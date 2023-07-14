#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "json.hpp"
#include "HTTPRequest.hpp"

using json = nlohmann::json;

std::string URL = "http://47.115.225.58:9023/planeController/getData";
const std::string FILEPATH = "/Users/zeal/work/project/TestCPP/SendSystem/result.json";
static int count = 0;
int sendFile();
void delay();

int main(int argc, char const *argv[])
{
	while(1) {
		std::cout << "COUNT:: " << count << std::endl;
		sendFile();
		delay();
	}
	return 0;
}

int sendFile() {
	std::ifstream file(FILEPATH);
	json data = json::parse(file);
	file.close();

	if (NULL == data) return 1;
	// 构造对象
	std::string body = data.dump();
	std::cout << body << std::endl << std::endl;
	try
	{
		http::Request request{URL};
		const auto response = request.send("POST", body , {
			{"Content-Type", "application/json"}
		});
		int code = response.status.code;
		std::cout << "code: " << code << std::endl; // print the result
		std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
		if (code != 200) return 1;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Request failed, error: " << e.what() << '\n';
	}
    return 0;
}

void delay()
{
    clock_t start_time;//, cur_time;
    start_time = clock();//clock()返回当前时间
    for (; (clock() - start_time) < 300 * CLOCKS_PER_SEC;);//延迟30秒
	count++;
}