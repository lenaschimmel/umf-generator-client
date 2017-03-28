#include "network.h"

using boost::asio::ip::tcp;
using namespace std;

/**
 * Very light weight URL safe converter
 */
 string makeURLSafe(string s)
 {
	 string r = "";
	 for (unsigned int i = 0; i < s.size(); i++)
	 {
		switch (s[i]) {
			case '#':
				r += "%23";
				break;
			case ',':
				r += "%2C";
				break;
			case ':':
				r += "%3A";
				break;
			case ';':
				r += "%3B";
				break;
			default:
				r += s[i];
		}
	 }
	 return r;
 }


/**
 * DOWNLOAD
 */
int download(const char *server, const char *path, string &data)
{
	try
	{
		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(server, "http");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		// Try each endpoint until we successfully establish a connection.
		tcp::socket socket(io_service);
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end)
		{
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error)
		{
			throw boost::system::system_error(error);
		}

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		ostream request_stream(&request);
		request_stream << "GET " << path << " HTTP/1.0\r\n";
		request_stream << "Host: " << server << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		istream response_stream(&response);
		string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		string status_message;
		getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			cerr << "Invalid response\n";
			return 1;
		}
		if (status_code != 200)
		{
			cerr << "Download: Response returned with status code " << status_code << "\n";
			return 1;
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		string header;
		while (getline(response_stream, header) && header != "\r")
		{
			//cout << header << "\n";
		}
		//cout << "\n";
		
		
		ostringstream xmlStream;

		// Write whatever content we already have to output.
		if (response.size() > 0)
		{
			//cout << &response;
			xmlStream << &response;
		}

		// Read until EOF, writing data to output as we go.
		while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
		{
			xmlStream << &response;
		}
		if (error != boost::asio::error::eof)
		{
			throw boost::system::system_error(error);
		}
		
		data = xmlStream.str();
	
		//if (xmlString.length() > 0) {
		//	cout << xmlString << endl;
		//}
			
		return 0;
	}
	catch (exception& e)
	{
		cerr << "Exception: " << e.what() << "\n";
		return 1;
	}
}