

void read_from_file         (vector <pair<string,bool>>&,ifstream &);
void write_to_file          (vector <pair<string,bool>>&,ofstream &);
void add_task_to_vector     (pair<string,bool>,vector<pair<string,bool>>&);
void remove_task_from_vector(vector<pair<string,bool>>&,int);
void mark_task              (vector<pair<string,bool>>&,int);
void user_experience        (vector<pair<string,bool>>&);
void show_tasks             (const vector<pair<string,bool>>);
void show_menu              ();
int main(){
  // Declare the vector of tasks
  vector <pair <string,bool>> tasks;
  // read the tasks from the file   
  ifstream infile("task.txt",ios::app|ios::in);
  if(!infile.is_open()){
    cerr << "error opening the file!";
    return 1;
  }
  read_from_file(tasks,infile);
  infile.close();
  // User experience
  user_experience(tasks);
  // save the tasks to the file
  ofstream outfile("task.txt");
  if(!outfile.is_open()){
    cerr << "error opening the file!";
    return 1;
  }
  write_to_file(tasks,outfile);
  outfile.close();
}

void read_from_file(vector <pair<string,bool>>&tasks_vector,ifstream &tasks_file){
  string task,dummy;
  bool done;
  while(getline(tasks_file,task)){
    if(tasks_file >> done){
      // get rid of the new line char
      getline(tasks_file,dummy);
      tasks_vector.push_back(make_pair(task,done));
    }
  }
}
void write_to_file(vector <pair<string,bool>>&tasks_vector,ofstream &tasks_file){
  tasks_file.seekp(0,ios::beg);
  for(int i = 0;i < tasks_vector.size(); i++){
    tasks_file  << tasks_vector[i].first  << endl
                << tasks_vector[i].second << endl;
  }
}
void add_task_to_vector(pair<string,bool> task,vector<pair<string,bool>>&tasks_vector){
  if(task.first.length())
    tasks_vector.push_back(task);
}
void remove_task_from_vector(vector<pair<string,bool>>&tasks_vector,int location){
  if(location < tasks_vector.size() + 1)
    tasks_vector.erase(tasks_vector.begin() + location - 1);
}
void mark_task(vector<pair<string,bool>>&tasks_vector,int location){
  if(location < tasks_vector.size() + 1)
    tasks_vector[location - 1].second = !tasks_vector[location - 1].second;
}
void user_experience(vector<pair<string,bool>>&tasks_vector){
  int option;
  enum MenuOptions { ADD_TASK = 1, MARK_TASK, REMOVE_TASK, EXIT };
  do
  {
    system("cls");
    show_tasks(tasks_vector);
    show_menu();

    cin >> option;
    cin.ignore();

    string task;
    int location;

    switch(option){
      case ADD_TASK:
        cout << "write down the task:\n";
        cin >> task;
        add_task_to_vector(make_pair(task,0),tasks_vector);
        break;
      case MARK_TASK:
        cout << "enter a task to mark:\n";
        cin >> location;
        mark_task(tasks_vector,location);
        break;
      case REMOVE_TASK:
        cout << "enter a task to remove:\n";
        cin >> location;
        remove_task_from_vector(tasks_vector,location);
        break;
      case EXIT:
        break;
      default:
        cout << "invalid option!\n";
        break;
    }
  }while (option != EXIT);
  
}
void show_tasks(const vector<pair<string,bool>>tasks_vector){
  for (int i = 0; i < tasks_vector.size(); i++)
  {
    cout  << i + 1 << ". ";
    tasks_vector[i].second ? cout << '[' << 'x' << ']' : cout << '[' << ' ' << ']';
    cout << tasks_vector[i].first;
    cout << endl;
  }
  cout << endl;
}
void show_menu(){
  cout  << "1. add task\n"
        << "2. mark task\n"
        << "3. remove task\n"
        << "4. exit\n";
}
