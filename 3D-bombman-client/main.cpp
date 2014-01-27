//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//



#include <boost/asio.hpp>
#include <boost/format.hpp>
#include "chat_message.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "gametimer.h"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

std::string MsgToSend = "";
std::string IP;

std::string PORT;
void StartAndSend();























std::string now_str()
{
	// Get current time from the clock, using microseconds resolution
	const boost::posix_time::ptime now =
		boost::posix_time::microsec_clock::local_time();

	// Get the time offset in current day
	const boost::posix_time::time_duration td = now.time_of_day();

	//
	// Extract hours, minutes, seconds and milliseconds.
	//
	// Since there is no direct accessor ".milliseconds()",
	// milliseconds are computed _by difference_ between total milliseconds
	// (for which there is an accessor), and the hours/minutes/seconds
	// values previously fetched.
	//
	const long hours = td.hours();
	const long minutes = td.minutes();
	const long seconds = td.seconds();
	const long milliseconds = td.total_milliseconds() -
		((hours * 3600 + minutes * 60 + seconds) * 1000);

	//
	// Format like this:
	//
	//      hh:mm:ss.SSS
	//
	// e.g. 02:15:40:321
	//
	//      ^          ^
	//      |          |
	//      123456789*12
	//      ---------10-     --> 12 chars + \0 --> 13 chars should suffice
	//
	//
	char buf[40];
	sprintf(buf, "%02ld:%02ld:%02ld.%03ld",
		hours, minutes, seconds, milliseconds);

	return buf;
}

class chat_client
{
public:
	string Replacer(string Text, string WhatsToRemove, string WhatsToPutIn) {
		string ReturnString;
		for (int i = 0; i <= Text.length() - 1; i++) {
			if (Text.substr(i, WhatsToRemove.length()) == WhatsToRemove) {
				if (WhatsToPutIn != "") {
					ReturnString = ReturnString + WhatsToPutIn;
					i += (int)WhatsToRemove.length() - 1;
				}
			}
			else {
				ReturnString = ReturnString + Text.substr(i, 1);
			}
		}

		return ReturnString;
	}

	int StringCount(string Text, string WhatToCount) {
		if (Text.length() < WhatToCount.length()) {
			return 0;
		}
		int Count = 0;
		for (int i = 0; i < Text.length() - (WhatToCount.length() - 1); i++) {
			if (Text.substr(i, WhatToCount.length()) == WhatToCount) {
				Count++;
			}
		}
		return Count;
	}

	string* Splitter(string Text, string StringToSplitAt) {
		int Length = StringCount(Text, StringToSplitAt);
		string *NewArray = new string[Length + 1];

		int Counter = 0;
		string RemaningText = Text;
		while (StringCount(RemaningText, StringToSplitAt) != 0) {
			NewArray[Counter] = RemaningText.substr(0, RemaningText.find(StringToSplitAt));
			RemaningText = RemaningText.substr(RemaningText.find(StringToSplitAt) + StringToSplitAt.length(), RemaningText.length() - 1);
			Counter++;
		}
		NewArray[Counter] = RemaningText;

		string* Pointer = NewArray;
		return Pointer;
	}
	chat_client(boost::asio::io_service& io_service,
		tcp::resolver::iterator endpoint_iterator)
		: io_service_(io_service),
		socket_(io_service)
	{
		do_connect(endpoint_iterator);
	}

	void write(const chat_message& msg)
	{
		io_service_.post(
			[this, msg]()
		{
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress)
			{
				do_write();
			}
		});
	}

	void close()
	{
		io_service_.post([this]() { socket_.close(); });
	}

private:
	void do_connect(tcp::resolver::iterator endpoint_iterator)
	{
		boost::asio::async_connect(socket_, endpoint_iterator,
			[this](boost::system::error_code ec, tcp::resolver::iterator)
		{
			if (!ec)
			{
				do_read_header();
			}
		});
	}

	void do_read_header()
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec && read_msg_.decode_header())
			{
				do_read_body();
			}
			else
			{
				socket_.close();
			}
		});
	}
	std::string MyPID;
	bool Started = false;
	std::string CTSS(char *Arr, int Length) {
		std::string ReturnS = "";
		for (int i = 0; i < Length; i++) {
			ReturnS += Arr[i];
		}
		return ReturnS;
	}
	chat_message CTS(std::string str) {
		std::string MsgToSend = str;
		char line[chat_message::max_body_length + 1];
		for (int i = 0; i < MsgToSend.length(); i++) {
			line[i] = MsgToSend[i];
		}
		chat_message msg;
		msg.body_length(MsgToSend.length());
		std::memcpy(msg.body(), line, msg.body_length());
		msg.encode_header();
		return msg;
	}
	template <typename T> string tostr(const T& t) { ostringstream os; os << t; return os.str(); }
	void do_read_body()
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				string Data = CTSS(read_msg_.body(), read_msg_.body_length());
				//cout <<  "Modtaget: " << Data << "\n";
				if (MyPID == "") {
					MyPID = read_msg_.body()[0];
					MyPID += read_msg_.body()[1];
				}

				string *Data2 = Splitter(Data, ";;;");
				int Counter = 0;
				for (int i = 0; i <= StringCount(Data, ";;;"); i++) {
					if (StringCount(Data2[i], ";") >= 2) {
						string *Data3 = Splitter(Data2[i], ";");
						float PosXX = atof(Data3[1].c_str());
						float PosZZ = atof(Data3[2].c_str());
						if (Data3[0] != MyPID) {
							OtherPos[Counter].x = atof(Data3[1].c_str());
							OtherPos[Counter].z = atof(Data3[2].c_str());
							Counter++;
						}
						int Oi = i;
						for (int i = 0; i < StringCount(Data2[Oi], ";") - 2; i++) {
							if (Data3[i + 3] == "B") {
								BombWorld[(int)PosXX][(int)PosZZ].armed = true;
								BombWorld[(int)PosXX][(int)PosZZ].power = PlayerPower;
								BombWorld[(int)PosXX][(int)PosZZ].WasItMeWhoPlaced = true;
							}
						}
						cout << OtherPos[Counter].x << " - " << OtherPos[Counter].z << "\n";
					}
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				string SendText = (MyPID + ";" + tostr(BodyPosition.x) + ";" + tostr(BodyPosition.z));
				if (PlaceNextTime) {
					PlaceNextTime = false;
					if (!BombWorld[(int)BodyPosition.x][(int)BodyPosition.z].armed && MaksBombs != 0) {

						SendText += ";B";
					}
				}
				write(CTS(SendText));
				//cout << "Sendt: " << MyPID + ";" + tostr(BodyPosition.x) + ";" + tostr(BodyPosition.z) << "\n";
				do_read_header();
				//std::cout.write(read_msg_.body(), read_msg_.body_length());
				/*std::cout << " - " << MyPID << "\n";


				MsgToSend = "HejHejHej";
				char line[chat_message::max_body_length + 1];
				for (int i = 0; i < MsgToSend.length(); i++) {
				line[i] = MsgToSend[i];
				}
				chat_message msg;
				msg.body_length(std::strlen(line));
				std::memcpy(msg.body(), line, msg.body_length());
				msg.encode_header();

				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				write(msg);*/
			}
			else
			{
				socket_.close();
			}
		});
	}

	void do_write()
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
			write_msgs_.front().length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				write_msgs_.pop_front();
				if (!write_msgs_.empty())
				{
					do_write();
				}
			}
			else
			{
				socket_.close();
			}
		});
	}

private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};



int main(int argc, char* argv[])
{
	try
	{
		std::cout << "Server IP:\n";
		std::cin >> IP;

		std::cout << "Server PORT:\n";
		std::cin >> PORT;

		if (argc != 3)
		{
			//std::cerr << "Usage: chat_client <host> <port>\n";
			//return 1;
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ IP, PORT });
		chat_client c(io_service, endpoint_iterator);
		std::thread t([&io_service](){ io_service.run(); });

		/*****************************************************************************************************************
		*********************************************************GLUT*****************************************************
		*****************************************************************************************************************/

		// init GLUT and create window
		glutInit(&argc, argv);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(1360, 700);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
		glutCreateWindow("3D bombman");
		glutSetCursor(GLUT_CURSOR_NONE);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_POLYGON_OFFSET_POINT);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0, 1.0);

		//glutFullScreen();
		WallTex = texture::loadBMP("stone.bmp");
		CrateTex = texture::loadBMP("crate.bmp");
		BombTex = texture::loadBMP("bomb.bmp");
		FireTex = texture::loadBMP("fire.bmp");
		//Register callbacks
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutMotionFunc(MouseMotion);
		glutPassiveMotionFunc(MouseMotion);
		glutIdleFunc(Gametimer);
		glutKeyboardFunc(KeyBoardCallBackDown);
		glutKeyboardUpFunc(KeyBoardCallBackUp);



		glutMainLoop();
		/*****************************************************************************************************************
		*************************************************GLUT FINISHED****************************************************
		*****************************************************************************************************************/

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

void StartAndSend() {

	try {




	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
}