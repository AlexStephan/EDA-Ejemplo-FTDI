#include "Twitter_Model.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using json = nlohmann::json;
static size_t curlWriteData(void* contents, size_t size, size_t nmemb, void* userp);

Twitter_Model::Twitter_Model() : user(), tuit(), date(), token(), speed(5), numberOfTweets(1), currentTweetNumber(1), status(statusType::WELCOME), error(errorType::NONE)
{
	getBearerToken();
}

void Twitter_Model::getBearerToken()
{
	json tokenJson;
	curlEasy = curl_easy_init();

	if (curlEasy)
	{
		curl_easy_setopt(curlEasy, CURLOPT_URL, "https://api.twitter.com/oauth2/token");
		curl_easy_setopt(curlEasy, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curlEasy, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
		curl_easy_setopt(curlEasy, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_easy_setopt(curlEasy, CURLOPT_USERPWD, "a4aTMoBFL2zhFxpQzQFF3vOWd:wmQb14JbMG8koWmu65nVOrmKlJDJWaW7nw86da2cMKaXiqGoeT");
		struct curl_slist* list = NULL;
		list = curl_slist_append(list, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curlEasy, CURLOPT_POSTFIELDSIZE, strlen("grant_type=client_credentials"));
		curl_easy_setopt(curlEasy, CURLOPT_POSTFIELDS, "grant_type=client_credentials");
		curl_easy_setopt(curlEasy, CURLOPT_HTTPHEADER, list);
		curl_easy_setopt(curlEasy, CURLOPT_WRITEFUNCTION, curlWriteData);
		curl_easy_setopt(curlEasy, CURLOPT_WRITEDATA, &token);
		curl_easy_setopt(curlEasy, CURLOPT_SSL_VERIFYPEER, 0L);

		CURLcode c = curl_easy_perform(curlEasy);

		if (c != CURLE_OK)
		{
			error = errorType::CANT_CONNECT;
		}
		curl_easy_cleanup(curlEasy);
	}
	tokenJson = json::parse(token);
	token = tokenJson["access_token"];
	this->notifyAllObservers();
}

void Twitter_Model::continueLoading()
{
	int runningHandles = 1;
	curl_multi_perform(curl, &runningHandles);

	if (runningHandles == 0)
	{
		status = statusType::FINISHED_LOADING;
		this->notifyAllObservers();
	}
}

void Twitter_Model::startLoading()
{
	tuit.clear();
	date.clear();
	currentTweetNumber = 1;
	tweets = "";
	tweetsString.clear();
	curl = curl_multi_init();
	curlEasy = curl_easy_init();

	if (numberOfTweets > 0)
	{
		std::string url = "https://api.twitter.com/1.1/statuses/user_timeline.json?";
		std::string screenName = "screen_name=" + user;
		std::string twCount = "count=" + std::to_string(numberOfTweets);
		url += screenName;
		url += '&';
		url += twCount;
		url += "&tweet_mode=extended";
		curl_easy_setopt(curlEasy, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curlEasy, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curlEasy, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curlEasy, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS | CURLPROTO_HTTP);
		curl_easy_setopt(curlEasy, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		struct curl_slist* list = NULL;
		std::string auth = "Authorization: Bearer ";
		auth += token;
		list = curl_slist_append(list, auth.c_str());
		curl_easy_setopt(curlEasy, CURLOPT_HTTPHEADER, list);
		curl_easy_setopt(curlEasy, CURLOPT_WRITEFUNCTION, curlWriteData);
		curl_easy_setopt(curlEasy, CURLOPT_WRITEDATA, &tweetsString);


		curl_multi_add_handle(curl, curlEasy);
		status = statusType::LOADING;
		this->notifyAllObservers();
	}
	else
		error = errorType::NO_TWEETS_AVAILABLE;

}

void Twitter_Model::stopLoading()
{
	curl_multi_remove_handle(curl, curlEasy);
	curl_easy_cleanup(curlEasy);
	curl_multi_cleanup(curl);

	try {
		tweets = json::parse(tweetsString);
		std::ofstream output("tweet.json");
		output << std::setw(4) << tweets << std::endl;
		output.close();
	}
	catch (std::exception& e)
	{
		json::iterator it = tweets.end();
		it--;
		tweets.erase(it);
	}

	if (tweets.empty())
	{
		error = errorType::NO_TWEETS_AVAILABLE;
	}
	this->notifyAllObservers();
}

void Twitter_Model::endModel()
{
	status = statusType::GOODBYE;
	this->notifyAllObservers();
}

void Twitter_Model::readTweet() {
	status = statusType::SHOW_TWEET;
	this->notifyAllObservers();
}


//GETTERS

const char* Twitter_Model::getUser()
{ 
	return user.c_str(); 
}

const char* Twitter_Model::getTuit() 
{
	tuit = tweets[currentTweetNumber - 1]["full_text"];
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