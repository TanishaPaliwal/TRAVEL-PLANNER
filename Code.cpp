
#include <iostream>
#include <map>
#include <list>
#include <set>
#include<vector>

using namespace std;

int fare=8; //8 rupees per km
template<typename T>
class Graph{

	map<T, list<pair<T,int> > > mapIndia;

public:

	void addEdge(T place1,T place2,int distance,bool bidir=true){

		mapIndia[place1].push_back(make_pair(place2,distance));

		if(bidir){

			mapIndia[place2].push_back(make_pair(place1,distance));

		}

	}



	void printAdj(){

		//Iterate over all the key value pairs in the map

		for(auto it : mapIndia){

			cout<<it.first<<"->";

			//Iterater over the list of cities

			for(auto it2 : it.second){

				cout<<"("<<it2.first<<","<<it2.second<<")";

			}

			cout<<endl;

		}
	}

	void dijsktraSSSP(T source){
		map<T,int> distance;
		map<T, T> parent;
		//Set all distance to infinity

		for(auto it:mapIndia){

			distance[it.first] = INT_MAX;
			parent[it.first] = "source";

		}



		//Make a set to find a node with the minimum distance
		set<pair<int, T> > s;

		distance[source] = 0;

		s.insert(make_pair(0,source));


		while(!s.empty()){

			//Find the pair at the front.

			auto p =   *(s.begin());

			T nodePlace = p.second;

			int nodeDist = p.first;

			s.erase(s.begin());

			//Iterate over children

			for(auto childPair: mapIndia[nodePlace]){

				if(nodeDist + childPair.second < distance[childPair.first]){

					//remove the old pair, and insert the new pair

					T destination = childPair.first;

					auto f = s.find( make_pair(distance[destination],destination));

					if(f!=s.end()){

						s.erase(f); }
					//Insert the new pair

					distance[destination] = nodeDist + childPair.second;

					s.insert(make_pair(distance[destination],destination));

					parent[destination] = nodePlace;

				}
			}

		}

		//print distance to all other node from src

		for(auto d:distance){


			cout<<d.first<<" is located at distance of "<<d.second<<"Km from "<<source<<endl;
			cout<<"Fare for the trip : Rs."<<(d.second * fare)<<endl;
			cout<<"The path to "<<d.first<<" is: "<<endl;
			T curr_city = d.first;
			vector<T> route;
			while(true){
				if(curr_city == "source") break;
				route.push_back(curr_city);
				curr_city = parent[curr_city];
			}
			for(int i=route.size()-1;i>=0;i--){
				cout<<route[i]<<" ";
			}
			cout<<endl<<endl; }
	}
};


void CreateGraph(Graph<string>&india)
{
	india.addEdge("Amritsar","Delhi",450);

	india.addEdge("Amritsar","Jaipur",687);

	india.addEdge("Jaipur","Delhi",278);

	india.addEdge("Jaipur","Mumbai",1147);

	india.addEdge("Bhopal","Agra",557);

	india.addEdge("Mumbai","Bhopal",775);

	india.addEdge("Agra","Delhi",231);
}

int main(){

	//	Graph<int> g;
	//
	//	g.addEdge(1,2,1);
	//
	//	g.addEdge(1,3,4);
	//
	//	g.addEdge(2,3,1);
	//
	//	g.addEdge(3,4,2);
	//
	//	g.addEdge(1,4,7);
	//
	//	g.printAdj();
	//
	//	g.dijsktraSSSP(1);
	//
	//	india.printAdj();
	//
	//	india.dijsktraSSSP("Amritsar");

	cout<<"=============================="<<endl;
	cout<<"WELCOME TO OUR TRAVEL PLANNER"<<endl;
	cout<<"=============================="<<endl;
	cout<<endl;
	Graph<string> india;
	CreateGraph(india);


	char ch;
	string src;
	while (ch != 'n')
	{
		cout << "Do you want to continue : y/n"<<endl;
		cin >> ch;
		if(ch=='n')
		{
			cout<<"THANK YOU FOR TRAVELLING WITH US";
			break;
		}

		cout << "Enter your source city : "<<endl;
		cin >> src;

		india.printAdj();

		india.dijsktraSSSP(src);
	}


	cout<<endl;

	return 0;
}
