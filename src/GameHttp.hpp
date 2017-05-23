#ifndef GAMEHTTP_HPP
#define GAMEHTTP_HPP

#include <string>

class GameHttp{
	public:
		GameHttp();
		GameHttp(bool dontInitialize);
		~GameHttp();
		void Init();
		int registerUser(std::string username , std::string password); // return 1 for success ; 0 for failure
		int loginUser(std::string username , std::string password); // 1 ok , 0 fail
		std::string lastResponse;
		std::string getServerlistJSON();
		
	private:
		void netAndHttpInit();
		void netAndHttpTerm();
		bool initializedHttp = false;
		
		
};



#endif