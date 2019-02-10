#include <cstdlib>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <zmq.hpp>
#include "GreenHouseSensorsListener.hpp"

const std::string QUERY_STRING="QUERY_STRING";
const std::string REQUEST_METHOD="REQUEST_METHOD";

void
json200header( std::ostream &out)
{
  out << "Status: 200 OK\r" << std::endl;
  out << "Content-Type: application/json;charset: utf-8\r" << std::endl;
  out << "Pragma: no-cache\r" << std::endl;
  out << "\r" << std::endl;
}

void
plainTextHeader(std::ostream &out)
{
  out << "Status: 200 OK\r" << std::endl;
  out << "Content-Type: application/text;charset: utf-8\r" << std::endl;
  out << "Pragma: no-cache\r" << std::endl;
  out << "\r" << std::endl;
}

void
header503(std::ostream &out)
{
  out << "Status: 503 OK\r" << std::endl;
  out << "Content-Type: application/text;charset: utf-8\r" << std::endl;
  out << "Pragma: no-cache\r" << std::endl;
  out << "\r" << std::endl;
}


std::vector<std::string>
split(const std::string &input, char sep)
{
  std::vector<std::string> result;
  std::istringstream ss(input);
  std::string s;
  while(std::getline(ss, s, sep)) {
    result.push_back(s);
  }
  return result;
}

void
parseQueryString(const char* queryString, std::map<std::string, std::string> &keyValueMap)
{
  keyValueMap.clear();
  std::vector<std::string> paramsSplit = split(queryString, '&');
  for (std::string &keyVal : paramsSplit) {
    std::vector<std::string> keyValSplit = split(keyVal, '=');
    if(keyValSplit.size() == 2) {
      keyValueMap[keyValSplit[0]]=keyValSplit[1];
    } else if (keyValSplit.size() == 1) {
      keyValueMap[keyValSplit[0]]= "";
    } else {
      std::string s = queryString;
      throw std::runtime_error("Error parsing query string" + s);
    }
  }
}

void
processHttpRequest(std::map<std::string, std::string> &keyValueMap)
{
  // setting GET as default allow launching the executable from command line                                                                                                                                                              
  const char* requestMethod = getenv(REQUEST_METHOD.c_str());
  if (!requestMethod) {
    requestMethod = "GET";
  }
  if (requestMethod == "POST") {
    std::string queryString;
    while (std::cin >> queryString) {
      parseQueryString(queryString.c_str(), keyValueMap);
    }
    keyValueMap[REQUEST_METHOD] = "POST";
  } else if (requestMethod == "GET") {
    parseQueryString(getenv(QUERY_STRING.c_str()), keyValueMap);
    keyValueMap[REQUEST_METHOD] = "GET";
  } else {
    throw std::runtime_error("Unsupported HTTP REQUEST METHOD " + std::string(requestMethod));
  }
  
}

void
serialize(const std::map<std::string, std::string> &map, std::ostream &out)
{

  std::stringstream ss(std::ios::in|std::ios::out);
  out << "{" << std::endl;
  for (std::map<std::string,std::string>::const_iterator it = map.begin();
       it != map.end();
       ++it)
    {
      if (it != map.begin()) {
	out << "," << std::endl;
      }
      out << "'" << it->first << "':'" << it->second<<"'";
    }
  out  << std::endl << "}" << std::endl;
}

const std::string PARAMETER_HUMIDITY= "humidity";
const std::string PARAMETER_TEMPERATURE= "temperature";
const std::string WATER_LEVEL = "waterLevel";



/**
 * CGI-Bin executable to handle requests to greenhouse data an
 * TODO: set up lighthttpd or apache2 to handle this executable
 */
int
main(int argc, char *argv[])
{

  std::map<std::string, std::string> parametersMap;
  processHttpRequest(parametersMap);

  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REQ);
  std::cout << "Connecting to hello world server…" << std::endl;
  socket.connect ("tcp://localhost:6533");

  if (parametersMap.find("sensors") != parametersMap.end()) {
    zmq::message_t request (7);
    memcpy (request.data (), "sensors", 7);
    socket.send (request);
    zmq::message_t reply;
    socket.recv (&reply);
    GreenHouseSensorMeasure measure;
    memcpy(&measure, reply.data(), sizeof(GreenHouseSensorMeasure));
    json200header(std::cout);
    asJson(std::cout, measure);
  } else if (parametersMap.find("tap") != parametersMap.end()) {
    zmq::message_t request(3);
    memcpy(request.data(), "tap", 3);
    socket.send(request);
    zmq::message_t reply;
    socket.recv(&reply);
    plainTextHeader(std::cout);
    std::cout << "OK" << std::endl;
  } else {
    header503(std::cout);
  }
   

  
}
