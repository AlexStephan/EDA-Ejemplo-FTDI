#include "Twitter_Model.h"
#include <iostream>
#include <fstream>
#include <string>


using json = nlohmann::json;
static size_t curlWriteData(void* contents, size_t size, size_t nmemb, void* userp);

Twitter_Model::Twitter_Model() : user(NULL), tuit(NULL), date(NULL), token(NULL), speed(5), numberOfTweets(1), currentTweetNumber(1), status(statusType::WELCOME), error(errorType::NONE)
{
	getBearerToken();
}

void Twitter_Model::getBearerToken()
{
	json tokenJson;
	std::string path = "https://api.twitter.com/oauth2/token";

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, sizeof("grant_type=client_credentials"));
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");
		curl_easy_setopt(curl, CURLOPT_USERPWD, "mHNUHhKMeOMP8uSe1jI26Uzw8:cOlmgKA4Dv1ILoNQa8G3uHrmEZZ7IdrcXpgopZkH5sdRT0mQHx");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteData);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &token);

		if (curl_easy_perform(curl) != CURLE_OK)
		{
			error = errorType::CANT_CONNECT;
		}
		curl_easy_cleanup(curl);
	}
	tokenJson = json::parse(token);
	token = tokenJson["access_token"];
	this->notifyAllObservers();
}

void Twitter_Model::downloadTweets(void)
{
	int runningHandles = 1;
	int curlMessages;
	CURLMsg* curlMsg;

	if (status != statusType::LOADING)
	{
		curl = curl_multi_init();
		CURL* curlEasy = curl_easy_init();

		std::string url = "https://api.twitter.com/1.1/statuses/user_timeline.json?";
		std::string screenName = "screen_name=" + user;
		std::string twCount = "count=" + std::to_string(numberOfTweets);
		url += screenName;
		url += '&';
		url += twCount;

		curl_easy_setopt(curlEasy, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteData);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tweetsString);
		curl_multi_add_handle(curl, curlEasy);
		status = statusType::LOADING;
	}

	curl_multi_perform(curl, &runningHandles);
	while ((curlMsg = curl_multi_info_read(curl, &curlMessages))->msg != CURLMSG_DONE && curlMessages != 0)
	{
		if (curlMsg->data.result != CURLE_OK)
		{
			error = errorType::CANT_CONNECT;
		}
	}

	if (curlMsg->msg == CURLMSG_DONE || status == statusType::STOPPED_LOADING)
	{
		status = statusType::FINISHED_LOADING;
		tweets = json::parse(tweetsString);

		if (tweets.size() == 0)
		{
			error = errorType::NO_TWEETS_AVAILABLE;
		}
	}

	this->notifyAllObservers();
}




//GETTERS

const char* Twitter_Model::getUser()
{ 
	return user.c_str(); 
}

const char* Twitter_Model::getTuit() 
{
	tuit = tweets[currentTweetNumber - 1]["text"];
	return tuit.c_str();
}

const char* Twitter_Model::getDate() 
{
	date = tweets[currentTweetNumber - 1]["created_at"];
	return date.c_str();
}

double Twitter_Model::getSpeed() 
{
	return speed;
}

errorType::errorVar Twitter_Model::getError() 
{
	return error;
}

statusType::statusVar Twitter_Model::getStatus()
{ 
	return status; 
}

unsigned int Twitter_Model::getNumberOfTweets() 
{
	numberOfTweets = tweets.size();
	return numberOfTweets;
}

unsigned int Twitter_Model::getCurrentTweetNumber() 
{
	return currentTweetNumber;
}





//SETTERS

void Twitter_Model::setUser(const char* user)
{
	this->user = user;
}

void Twitter_Model::setSpeed(double speed)
{
	this->speed = speed;
}

void Twitter_Model::setCurrentTweetNumber(unsigned int currentTweet)
{
	this->currentTweetNumber = currentTweet;
}

void Twitter_Model::setNumberOfTweets(unsigned int nOfTweets)
{
	this->numberOfTweets = nOfTweets;
}



//Funcion para recibir data en Curl

static size_t curlWriteData(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	char* data = (char*)contents;
	std::string* s = (std::string*)userp;
	s->append(data, realsize);
	return realsize;					
}