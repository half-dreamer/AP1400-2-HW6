#ifndef Q3_H
#define Q3_H

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

namespace q3
{
    struct Flight
    {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };

    inline size_t TimeStrToNum(string timeStr)
    {
        size_t hourPos = timeStr.find('h');
        size_t hour = stoi(timeStr.substr(0, hourPos));

        size_t minutePos = timeStr.find('m');
        size_t minute = 0;
        if (minutePos != string::npos){
            minute = stoi(timeStr.substr(hourPos + 1, minutePos - hourPos - 1));
        }
        return hour * 60 +  minute;
    }
    class Compare {
        public :
            bool operator()(Flight a, Flight b)
            {
                size_t priorOfA = a.duration + a.connection_times + 3 * a.price;
                size_t priorOfB = b.duration + b.connection_times + 3 * b.price;
                return priorOfA > priorOfB;
            }
    };

    inline std::priority_queue<Flight, vector<Flight>, Compare> gather_flights(string fileName)
    {
        priority_queue<Flight, vector<Flight>, Compare> pq;
        ifstream ifs(fileName);
        string fileLine;
        size_t startPos, endPos;
        while (getline(ifs, fileLine))
        {
            startPos = fileLine.find(':');
            fileLine = fileLine.substr(startPos + 1);
            endPos = fileLine.find(' ');
            string flight_num = fileLine.substr(0, endPos);

            startPos = fileLine.find(':');
            fileLine = fileLine.substr(startPos + 1);
            endPos = fileLine.find(' ');
            string durationStr = fileLine.substr(0, endPos);
            size_t duration = TimeStrToNum(durationStr);

            startPos = fileLine.find(':');
            fileLine = fileLine.substr(startPos + 1);
            size_t connections = stoi(fileLine.substr(0, 1));

            startPos = fileLine.find(':');
            fileLine = fileLine.substr(startPos + 1);
            size_t connection_times = 0;
            for (int i = 0; i < connections - 1; i++)
            {
                endPos = fileLine.find(',');
                connection_times += TimeStrToNum(fileLine.substr(0, endPos));
                fileLine = fileLine.substr(endPos + 1);
            }
            endPos = fileLine.find(' ');
            connection_times += TimeStrToNum(fileLine.substr(0, endPos));
            fileLine = fileLine.substr(endPos + 1);

            startPos = fileLine.find(':');
            size_t price = stoi(fileLine.substr(startPos + 1));

            Flight *addedFlight = new Flight{flight_num, duration, connections, connection_times, price};
            pq.push(*addedFlight);
        }
        return pq;
    }
};

#endif //Q3_H