#include <bits/stdc++.h>
#include <fstream>
using namespace std;

vector<string> split(string s){
  vector<string>ans;
  s.push_back(' ');
  string temp;
  for(int i=0;i<s.length();i++){
    if(s[i]==' '){
      ans.push_back(temp);
      temp.clear();
    }
    else
    temp.push_back(s[i]);
  }
  return ans;
}

int main() {
  string command;
  int no_of_slot;
  set<int>empty_parking_slot;
  set<int>occupied_parking_slot;
  map<string,int>slot_no_for_car_no;
  map<int,string>car_no_for_slot_no;
  map<string,int>driver_car_no_with_age;
  map<int,vector<int>>Slot_numbers_for_driver_of_age;
   
  string line;
  fstream myfile;
  myfile.open("input.txt");
  if (myfile.is_open())
  {
  
    getline (myfile,line);  
    vector<string>commands=split(line);
    no_of_slot=stoi(commands[1]);

  cout<<"Created parking of "<<no_of_slot<<" slots\n";
for(int i=1;i<=no_of_slot;i++){
    empty_parking_slot.insert(i);
  }
 int  i=0;
  while(getline(myfile,line)){
    commands.clear();
    commands=split(line);
    string c1=commands[0];
    // that means car is here for parking
    if(c1.compare("Park")==0){
      //car is here for parking
      string c2,c3;
      int driver_age;
      c2=commands[1];
      c3=commands[2];
      driver_age=stoi(commands[3]);
      //here c2 is car number
      // c4 is driver age
      if(empty_parking_slot.size()==0){
        cout<<"No slots are empty";
        continue;
      }     
      driver_car_no_with_age[c2]=driver_age;
      // searching for current nearest slot
      auto current_nearest_slot=empty_parking_slot.begin();
      empty_parking_slot.erase(current_nearest_slot);
      occupied_parking_slot.insert(*current_nearest_slot);

      //allocation of slot
      slot_no_for_car_no[c2]=*current_nearest_slot;
      Slot_numbers_for_driver_of_age[driver_age].push_back(*current_nearest_slot);
      car_no_for_slot_no[*current_nearest_slot]=c2;


      cout<<"Car with vehicle registration number "<<c2<<" has been parked at slot number "<<*current_nearest_slot<<"\n";
    }

    ///this means that car is here to leave; 
    else if(c1.compare("Leave")==0){
      int leaving_slot_number;
      leaving_slot_number=stoi(commands[1]);
      //if given slot no is already empty
      if(occupied_parking_slot.count(leaving_slot_number)==0){
        cout<<"Sorry for inconvienece but slot number "<<leaving_slot_number<<" is already empty\n";
        continue;
      }
      
      occupied_parking_slot.erase(leaving_slot_number);
      empty_parking_slot.insert(leaving_slot_number);
      
      // data for leaving car 
      string current_car_no = car_no_for_slot_no[leaving_slot_number];
      int  current_driver_age=driver_car_no_with_age[current_car_no];

    
      slot_no_for_car_no.erase(current_car_no);
      driver_car_no_with_age.erase(current_car_no);
      car_no_for_slot_no.erase(leaving_slot_number);

     auto beg=Slot_numbers_for_driver_of_age[current_driver_age].begin();
     int pos=0;
     
      for(auto k: Slot_numbers_for_driver_of_age[current_driver_age]){
        if(k==leaving_slot_number)break;
        pos++;
      }      
     Slot_numbers_for_driver_of_age[current_driver_age].erase(beg+pos);

      cout<<"Slot number "<<leaving_slot_number<<"  vacated, the car with vehicle registration number "<<current_car_no<<" left the space, the driver of the car was of age "<<current_driver_age<<"\n";
      
    }
    else if(c1.compare("Slot_numbers_for_driver_of_age")==0){
      int curr_driver_age;
    curr_driver_age=stoi(commands[1]);
      if(Slot_numbers_for_driver_of_age[curr_driver_age].empty()){
        cout<<"No slot have been allocated for the driver of age "<<curr_driver_age<<"\n";
        continue;
      }
        for(auto k: Slot_numbers_for_driver_of_age[curr_driver_age]){
        cout<<k<<" ";
      }    
      cout<<"\n";
    }

    else if(c1.compare("Slot_number_for_car_with_number")==0){
      string current_car_no;
      current_car_no=commands[1];
      if(slot_no_for_car_no[current_car_no]){
        cout<<slot_no_for_car_no[current_car_no]<<" ";
      }
      else{
        cout<<"there is no car parked with this car number in this parking";
      }
      cout<<"\n";

    }
    else if(c1.compare("Vehicle_registration_number_for_driver_of_age")==0){
      int curr_driver_age;
      cin>>curr_driver_age;

       for(auto k: Slot_numbers_for_driver_of_age[curr_driver_age]){
        string curr_car_no=car_no_for_slot_no[k];
        cout<<"Car with vehicle registration number "<<curr_car_no<<" has been parked at slot number "<<k<<"\n";
      }  
      
    }
  }
   
    myfile.close();
  }
  else cout << "Unable to open file"; 

  
}