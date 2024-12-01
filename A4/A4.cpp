#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

const char COMMA = ',';
const char SPACE = ' ';
const char DASH = '-';
const char DOLLAR_SIGN = '$';

const int NOT_CHANGED = -1;
const int DAY_SIZE = 30;
const int FIRST_DAY = 1;
const int LAST_DAY = 30;
const int START_TIME = 0;
const int END_TIME = 24;
const int MIN_PERCANTAGE = 0;
const int MAX_PERCANTAGE = 100;
const int PRECISION = 1;
const int FIRST_ID = 1;

const string MAX = "Max";
const string MIN = "Min";
const string NOT_EQ = "not_equal";

const string EMPCSV = "employees.csv";
const string SALCSV = "salary_configs.csv";
const string TEAMSCSV = "teams.csv";
const string WORKHOURCSV = "working_hours.csv";

const string REPORT_SALARIES = "report_salaries";
const string REPORT_EMP_SAL = "report_employee_salary";
const string REPORT_TEAM_SAL = "report_team_salary";
const string REPORT_TOTAL_HOURS_PER_DAY = "report_total_hours_per_day";
const string REPORT_EMP_PER_HOUR = "report_employee_per_hour";

const string SHOW_SAL_CONFIG = "show_salary_config";
const string UPDATE_SAL_CONFIG = "update_salary_config";
const string ADD_WORK_HOURS = "add_working_hours";
const string DELETE_WORK_HOURS = "delete_working_hours";
const string UPDATE_TEAM_BONUS = "update_team_bonus";
const string FIND_TEAMS_FOR_BONUS = "find_teams_for_bonus";

class Work_interval;
class Work_hours_per_day;
class Salary;
class Employee;
class Team;
class Company;

class Work_interval {
public:
    Work_interval(string interval) { set_start_end(interval); }
    Work_interval(int start_time, int end_time) { start = start_time; end = end_time; }
    int get_len() { return end - start; }
    bool does_overlap(int other_start_time, int other_end_time);
    bool is_in_this_hour(int start_hour, int end_hour);
private:
    void set_start_end(string interval);
    int start;
    int end;
    int Interval_length;
};

class Work_hours_per_day {
public:
    Work_hours_per_day(int _day) { day = _day; }
    void set_interval(string interval) { work_intervals.push_back(Work_interval(interval)); }
    bool set_interval(int start_time, int end_time);
    bool is_day_match(int _day) { return (day == _day); }
    bool is_work_in_this_hour(int start_hour, int end_hour);
    int get_total_hours();
private:
    int day;
    vector <Work_interval> work_intervals;
};

class Salary {
public:
    Salary(string lv, int base_sal, int sal_per_hour, int sal_extra, int work_hour, int tax);
    void set_configs(int base_sal, int sal_per_hour, int sal_extra, int work_hour, int tax);
    string get_level() { return level; }
    int calc_pure_salary();
    int calc_tax();
    int calc_bonus();
    int total_earning_with_bonus();
    int total_earning_after_tax();
    bool is_level_match(string input_level) { return level == input_level; }
    void set_curr_emp(Employee* curr_emp) { current_emp = curr_emp; }
    void print_configs();
    void update_configs(string configs);
private:
    int determine_hours(int& extra_hour);
    string level;
    int base_salary;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
    Employee* current_emp;
};

class Employee {
public:
    Employee(int emp_id, string emp_name, int emp_age, string emp_level);
    void assign_interval_to_day(int day, string interval);
    bool match_level(Salary* salary);
    bool is_id_match(int _id) { return (id == _id); }
    void join_team(Team* team) { employee_team = team; }
    string get_name() { return name; }
    int get_total_hours();
    int get_id() { return id; }
    int emp_team_bonus();
    int get_num_of_days_work_in_this_hour(int start_hour, int end_hour);
    void print_salary();
    void print_salary(string detailed);
    void print_summary_info();
    string add_work_hour(string working_time_info);
    string delete_work_day(int day);
    int get_day_hours(int day);
private:
    void set_salary(Salary* sal) { salary = sal; }
    Work_hours_per_day* find_by_day(int day);
    bool is_new_day(int day);
    string emp_team_id();
    int get_absent_days();
    bool set_new_interval(int day, int start_time, int end_time);
    void print_info();
    int id;
    string name;
    int age;
    string level;
    Salary* salary;
    vector <Work_hours_per_day> work_days;
    Team* employee_team;
};

class Team {
public:
    Team(int _id, int h_id, int min_bonus, float max_bonus_var);
    void add_team_member(Employee* member);
    int get_team_id() { return id; }
    int get_team_bonus() { return bonus_percantage; }
    void print_salary();
    bool is_id_match(int input_id) { return id == input_id; }
    bool update_bonus(int new_bonus);
    bool is_deserve_bonus();
    void sort_team_members();
    int get_total_hour() { return calc_total_working_hours(); }
    bool is_time_match(int input_time) { return get_total_hour() == input_time; }
private:
    Employee* represent_head();
    string get_head_name();
    void print_info();
    int calc_total_working_hours();
    float calc_avg_working_hour();
    vector <int> get_members_work_hours();
    int id;
    int head_id;
    int bonus_percantage;
    int bonus_min_working_hours;
    float bonus_working_hours_max_variance;
    vector <Employee*> team_members;
};

class Company {
public:
    void add_employee(int id, string name, int age, string level);
    void config_salary(string level, int base_sal, int sal_per_hour, int sal_extra,
                       int work_hour, int tax);
    void make_team(int id, int head_id, string member_ids, int min_bonus, float max_bonus);
    void set_employee_working_time(int id, int day, string interval);
    void print_salaries();
    void print_employee_salary(int emp_id);
    void print_team_salary(int team_id);
    void report_day_total_hours(int start_day, int end_day);
    void report_employee_per_hour(int start_hour, int end_hour);
    void show_salary_config(string salary_level);
    void update_salary_config(string salary_level, string configs);
    void update_team_bonus(int team_id, int new_bonus);
    void add_employee_work_hour(int emp_id, string working_time_info);
    void delete_employee_work_hours(int emp_id, int day);
    void find_teams_for_bonus();
    void sort_employees();
    void sort_teams_members();
private:
    void assign_salary();
    Employee* find_employee_by_id(int id);
    Team* find_team_by_id(int id);
    Salary* find_salary_by_level(string level);
    void print_days_total_working_hours(vector <int> days, vector <int>& days_total_hours);
    void print_days_with_borders(vector <int> days_to_be_reported,
                                 vector <int> days_total_hours , string border_mode);
    string find_days_by_border(vector <int> days_to_be_reported,
                               vector <int> days_total_hours, int border_val);
    void print_working_emps_avg(vector <int> hours_to_be_reported, vector <float>& averages);
    void print_avereges_by_border(vector <int> hours_to_be_reported, vector <float> avereges,
                                  string border_mode);
    string find_avgs_by_border(vector <int> hours_to_be_reported,
                               vector <float> averages, float border_val);
    void sort_teams_by_working_hours(vector <Team*> deserved_teams);
    void print_deserved_teams(vector <Team*> unsorted_teams);
    void sort_teams_by_id(vector <int> team_ids, vector <Team*> unsorted_teams);
    vector <int> find_teams_ids(vector <Team*> teams);
    vector <Employee*> employees;
    vector <Salary*> salaries;
    vector <Team*> teams;
};

stringstream replace_identifire(string line, char identifire)
{
    replace(line.begin(), line.end(), identifire, SPACE);
    stringstream _line(line);
    return _line;
}

vector <int> init_vec(vector <int> vec)
{
    for(int i = 0; i < vec.size(); i++)
        vec[i] = i + 1;
    return vec;
}

vector <int> init_vec(int start_vec, int end_vec)
{
    vector <int> vec;
    for(int i = start_vec; i <= end_vec ; i++)
        vec.push_back(i);
    return vec;
}

void print_line_separator()
{
    cout << "---" << endl;
}

vector <int> check_val_or_char(string str, char ch)
{
    stringstream seprate_str(str);
    string temp, identifier;
    vector <int> data;
    identifier = ch;
    while (seprate_str >> temp)
    {
        if(temp == identifier)
            data.push_back(NOT_CHANGED);
        else
            data.push_back(stoi(temp));
    }
    return data;
}

float calculate_variance(vector <int> nums, float mean)
{
    float variance = 0;
    for(int num : nums)
        variance += pow((num - mean),2);
    variance /= nums.size();
    return variance;
}

bool is_between(int num, int start, int end)
{
    bool b = num >= start && num <= end;
    return num >= start && num <= end;
}

bool is_between(int num, int start, int end, string not_equal)
{
    return num > start && num < end;
}

bool is_valid_times(int day, int start_time, int end_time)
{
    return is_between(day, FIRST_DAY, LAST_DAY) &&
           is_between(start_time, START_TIME, END_TIME) &&
           is_between(end_time, START_TIME, END_TIME) && (start_time < end_time);
}

bool is_valid_times(int start_time, int end_time, int interval_begininig, int interval_end)
{
    return is_between(start_time, interval_begininig, interval_end) && 
           is_between(end_time, interval_begininig, interval_end) && (start_time < end_time);
}

vector <int> give_numbers_in_interval(int interval_begining, int interval_ending)
{
    return init_vec(interval_begining, interval_ending);
}

int find_max(vector <int> nums)
{
    return *max_element(nums.begin(), nums.end());
}

float find_max(vector <float> nums)
{
    return *max_element(nums.begin(), nums.end());
}

int find_min(vector <int> nums)
{
    return *min_element(nums.begin(), nums.end());
}

float find_min(vector <float> nums)
{
    return *min_element(nums.begin(), nums.end());
}

float calculate_average(int sum, int num)
{
    float avg = sum;
    avg /= num;
    avg = round(avg * 10);
    avg /= 10;
    return avg;
}

void print_message(string message) 
{
    cout << message << endl;
}

vector <int> find_employee_ids(vector <Employee*> emps)
{
    vector <int> ids;
    for(Employee* emp : emps)
        ids.push_back(emp->get_id());
    return ids;
}

vector <Employee*> sort_employees_by_id(vector <Employee*> unsorted_emps)
{
    int num_of_emps = unsorted_emps.size();
    vector <int> emp_ids = find_employee_ids(unsorted_emps);
    sort(emp_ids.begin(), emp_ids.end());
    vector <Employee*> sorted_emps;

    for(int j = 0; j < emp_ids.size(); j++)
    {
        for(int i = 0; i < num_of_emps; i++)
        {
            if(unsorted_emps[i]->is_id_match(emp_ids[j]))
            {
                sorted_emps.push_back(unsorted_emps[i]);
                break;
            }
        } 
    }
    return sorted_emps;
}

void Work_interval::set_start_end(string interval)
{
    stringstream _interval = replace_identifire(interval, DASH);
    _interval >> start >> end;
}

bool Work_interval::does_overlap(int other_start_time, int other_end_time)
{
    return is_between(other_start_time, start, end, NOT_EQ) ||
           is_between(other_end_time, start, end, NOT_EQ) ||
           is_between(start, other_start_time, other_end_time, NOT_EQ) ||
           is_between(end, other_start_time, other_end_time, NOT_EQ);
}

bool Work_interval::is_in_this_hour(int start_hour, int end_hour)
{
    return is_between(start_hour, start, end) && is_between(end_hour, start, end);
}

int Work_hours_per_day::get_total_hours()
{
    int total_hours = 0;
    for(Work_interval interval : work_intervals)
        total_hours += interval.get_len();
    return total_hours;
}

bool Work_hours_per_day::set_interval(int start_time, int end_time)
{
    for(Work_interval current_interval : work_intervals)
        if(current_interval.does_overlap(start_time, end_time))
        {
            return false;
            break;
        }
    work_intervals.push_back(Work_interval(start_time, end_time));
    return true;
}

bool Work_hours_per_day::is_work_in_this_hour(int start_hour, int end_hour)
{
    for(Work_interval interval : work_intervals)
        if(interval.is_in_this_hour(start_hour, end_hour))
            return true;
    return false;
}

Salary::Salary(string lv, int base_sal, int sal_per_hour, int sal_extra, int work_hour, int tax) 
{
    level = lv;
    set_configs(base_sal, sal_per_hour, sal_extra,work_hour, tax);
}

void Salary::set_configs(int base_sal, int sal_per_hour, int sal_extra, int work_hour, int tax)
{
    if(base_sal != NOT_CHANGED)
        base_salary = base_sal;
    if(sal_per_hour != NOT_CHANGED)
        salary_per_hour = sal_per_hour;
    if(sal_extra != NOT_CHANGED)
        salary_per_extra_hour = sal_extra;
    if(work_hour != NOT_CHANGED)
        official_working_hours = work_hour;
    if(tax != NOT_CHANGED)
        tax_percentage = tax;
}

int Salary::determine_hours(int& extra_hour)
{
    extra_hour = current_emp->get_total_hours() - official_working_hours;
    if(extra_hour < 0)
    {
        extra_hour = 0;
        return current_emp->get_total_hours();
    }
    else
        return official_working_hours;
}

int Salary::calc_pure_salary()
{
    int pure_salary = 0;
    int official_hour, extra_hour;
    official_hour = determine_hours(extra_hour);

    pure_salary += base_salary;
    pure_salary += official_hour * salary_per_hour + extra_hour * salary_per_extra_hour;
    return pure_salary;
}

int Salary::calc_bonus()
{
    return round((calc_pure_salary() * current_emp->emp_team_bonus())/100.0);
}

int Salary::total_earning_with_bonus()
{
    float total_earning = 0;
    total_earning += calc_pure_salary();
    total_earning += calc_bonus();
    return total_earning;
}

int Salary::calc_tax()
{
    return round((tax_percentage * total_earning_with_bonus()) /100.0);
}

int Salary::total_earning_after_tax()
{
    int total_earning_after_tax = 0;
    int total_earning = 0;
    total_earning = total_earning_with_bonus();
    total_earning_after_tax = total_earning - calc_tax();
    return total_earning_after_tax;
}

void Salary::print_configs()
{
    cout << "Base Salary: " << base_salary << endl;
    cout << "Salary Per Hour: " << salary_per_hour << endl;
    cout << "Salary Per Extra Hour: " << salary_per_extra_hour << endl;
    cout << "Official Working Hours: " << official_working_hours << endl;
    cout << "Tax: " << tax_percentage << "%" << endl;
}

void Salary::update_configs(string configs)
{
    vector <int> seprate_configs = check_val_or_char(configs, DASH);
    int base_sal, sal_per_hour, sal_extra, work_hour, tax;

    base_sal = seprate_configs[0];
    sal_per_hour = seprate_configs[1];
    sal_extra = seprate_configs[2];
    work_hour = seprate_configs[3];
    tax = seprate_configs[4];
    set_configs(base_sal, sal_per_hour, sal_extra, work_hour, tax);
}

Employee::Employee(int emp_id, string emp_name, int emp_age, string emp_level)
{
    id = emp_id;
    name = emp_name;
    age = emp_age;
    level = emp_level;
    employee_team = NULL;
}
bool Employee::match_level(Salary* salary)
{
    if(level == salary->get_level())
    {
        set_salary(salary);
        return true;
    }
    return false;
}

bool Employee::is_new_day(int day)
{
    for(Work_hours_per_day work_day : work_days)
        if(work_day.is_day_match(day))
            return false;
    return true;
}

Work_hours_per_day* Employee::find_by_day(int day)
{
    for(int i = 0; i < work_days.size(); i++)
        if(work_days[i].is_day_match(day))
            return &work_days[i];
    return NULL;
}

void Employee::assign_interval_to_day(int day, string interval)
{
    if(is_new_day(day))
    {
        work_days.push_back(Work_hours_per_day(day));
        work_days.back().set_interval(interval);
    }
    else
        find_by_day(day)->set_interval(interval);
}

int Employee::get_total_hours()
{
    int total_hours = 0;
    for(Work_hours_per_day day : work_days)
        total_hours += day.get_total_hours();
    return total_hours;
}

int Employee::get_absent_days()
{
    int num_of_absent_days = 0;
    vector <int> days(DAY_SIZE);
    days = init_vec(days);
    for(int i = 0; i < days.size(); i++)
        for(Work_hours_per_day day : work_days)
            if(day.is_day_match(days[i]))
                num_of_absent_days++;
    return days.size() - num_of_absent_days;
}

int Employee::emp_team_bonus()
{
    if(employee_team != NULL)
        return employee_team->get_team_bonus();
    return 0;
}

string Employee::emp_team_id()
{
    if(employee_team != NULL)
        return to_string(employee_team->get_team_id());
    else
        return "N/A";
}

int Employee::get_num_of_days_work_in_this_hour(int start_hour, int end_hour)
{
    int num_of_days_worked = 0;
    for(Work_hours_per_day work_day : work_days)
        if(work_day.is_work_in_this_hour(start_hour, end_hour))
            num_of_days_worked++;
    return num_of_days_worked;
}

void Employee::print_salary()
{
    salary->set_curr_emp(this);
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Total Working Hours: " << get_total_hours() << endl;
    cout << "Total Earning: " << salary->total_earning_after_tax() << endl; 
    print_line_separator();
}

void Employee::print_info()
{
    cout << "ID: " << id <<endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Level: " << level << endl;
    cout << "Team ID: " << emp_team_id() << endl;
}

void Employee::print_salary(string detailed)
{
    salary->set_curr_emp(this);
    print_info();
    cout << "Total Working Hours: " << get_total_hours() << endl;
    cout << "Absent Days: " << get_absent_days() << endl;
    cout << "Salary: " << salary->calc_pure_salary() << endl;
    cout << "Bonus: " << salary->calc_bonus() << endl;
    cout << "Tax: " << salary->calc_tax() << endl;
    cout << "Total Earning: " << salary->total_earning_after_tax() << endl;
}

void Employee::print_summary_info()
{
    salary->set_curr_emp(this);
    cout << "Member ID: " << id << endl;
    cout << "Total Earning: " << salary->total_earning_after_tax() << endl;
}

bool Employee::set_new_interval(int day, int start_time, int end_time)
{
    Work_hours_per_day* founded_day = find_by_day(day);
    if(founded_day != NULL)
    {
        if(founded_day->set_interval(start_time, end_time))
            return true;
        return false;
    }
    else
    {
        work_days.push_back(Work_hours_per_day(day));
        if(work_days.back().set_interval(start_time, end_time))
            return true;
        return false;
    }
}

string Employee::add_work_hour(string working_time_info)
{
    int day, start_time, end_time;
    stringstream work_time_seperated(working_time_info);
    work_time_seperated >> day >> start_time >> end_time;
    if(is_valid_times(day, start_time, end_time))
    {
        if(set_new_interval(day, start_time, end_time))
            return "OK";
        return "INVALID_INTERVAL";
    }
    return "INVALID_ARGUMENTS";
}

string Employee::delete_work_day(int day)
{
    if(!is_between(day, FIRST_DAY, LAST_DAY))
        return "INVALID_ARGUMENTS";
    for(int i = 0; i < work_days.size(); i++)
    {
        if(work_days[i].is_day_match(day))
            work_days.erase(work_days.begin() + i);
    }
    return "OK";
}

int Employee::get_day_hours(int day)
{
    Work_hours_per_day* mentioned_day = find_by_day(day);
    if(mentioned_day == NULL)
        return 0;
    return mentioned_day->get_total_hours();
}

Team::Team(int _id, int h_id, int min_bonus, float max_bonus_var)
{
    id = _id;
    head_id = h_id;
    bonus_percantage = 0;
    bonus_min_working_hours = min_bonus;
    bonus_working_hours_max_variance = max_bonus_var;
}

void Team::add_team_member(Employee* member)
{
    team_members.push_back(member);
    member->join_team(this);
}

Employee* Team::represent_head()
{
    for(Employee* member : team_members)
        if(member->is_id_match(head_id))
            return member;
    return NULL;
}

string Team::get_head_name()
{
    Employee* head = represent_head();
    return head->get_name();
}

int Team::calc_total_working_hours()
{
    int total_time = 0;
    for(Employee* member : team_members)
        total_time += member->get_total_hours();
    return total_time;
}

float Team::calc_avg_working_hour()
{
    return calculate_average(calc_total_working_hours(), team_members.size());
}

vector <int> Team::get_members_work_hours()
{
    vector <int> work_hours;
    for(Employee* team_member : team_members)
        work_hours.push_back(team_member->get_total_hours());
    return work_hours;
}

bool Team::update_bonus(int new_bonus)
{
    if(is_between(new_bonus, MIN_PERCANTAGE, MAX_PERCANTAGE))
    {
        bonus_percantage = new_bonus;
        return true;
    }
    return false;
}

bool Team::is_deserve_bonus()
{
    vector <int> work_hours = get_members_work_hours();
    float work_hours_var = calculate_variance(work_hours, calc_avg_working_hour());
    int total_work_hours = calc_total_working_hours();
    return (total_work_hours > bonus_min_working_hours) &&
        (work_hours_var < bonus_working_hours_max_variance);
}

void Team::print_info()
{
    cout << "ID: " << id << endl;
    cout << "Head ID: " << head_id << endl;
    cout << "Head Name: " << get_head_name() << endl;
    cout << "Team Total Working Hours: " << calc_total_working_hours() << endl;
    cout << "Average Member Working Hours: ";
    cout << fixed << setprecision(PRECISION) << calc_avg_working_hour() << endl;
    cout << "Bonus: " << bonus_percantage << endl;
}

void Team::print_salary()
{
    print_info();
    for(Employee* member : team_members)
    {
        print_line_separator();
        member->print_summary_info();
    }
    print_line_separator();
}

void Team::sort_team_members()
{
    team_members = sort_employees_by_id(team_members);
}

void Company::add_employee(int id, string name, int age, string level)
{
    employees.push_back(new Employee(id, name, age, level));
}

void Company::config_salary(string level, int base_sal, int sal_per_hour, int sal_extra,
                            int work_hour, int tax)
{
    salaries.push_back(new Salary(level, base_sal, sal_per_hour, sal_extra, work_hour, tax));
    assign_salary();          
}

void Company::make_team(int id, int head_id, string member_ids, int min_bonus, float max_bonus)
{
    int mem_id;
    stringstream mem_ids = replace_identifire(member_ids, DOLLAR_SIGN);
    teams.push_back(new Team(id, head_id, min_bonus, max_bonus));

    while (mem_ids >> mem_id)
        teams.back()->add_team_member(find_employee_by_id(mem_id));
}

void Company::assign_salary()
{
    for(Employee* employee : employees)
        for(Salary* salary : salaries)
            if(!employee->match_level(salary))
                continue;
}

Employee* Company::find_employee_by_id(int id)
{
    for(Employee* employee : employees)
        if(employee->is_id_match(id))
            return employee;
    return NULL;
}

Team* Company::find_team_by_id(int id)
{
    for(Team* team : teams)
        if(team->is_id_match(id))
            return team;
    return NULL;
}

Salary* Company::find_salary_by_level(string level)
{
    for(Salary* salary : salaries)
        if(salary->is_level_match(level))
            return salary;
    return NULL;
}

void Company::set_employee_working_time(int id, int day, string interval)
{
    Employee* employee = find_employee_by_id(id);
    employee->assign_interval_to_day(day, interval);
}

void Company::print_salaries()
{
    for(Employee* employee : employees)
        employee->print_salary();
}

void Company::print_employee_salary(int emp_id)
{
    string detailed;
    Employee* founded_emp = find_employee_by_id(emp_id);
    if(founded_emp != NULL)
        founded_emp->print_salary(detailed);
    else
        print_message("EMPLOYEE_NOT_FOUND");
}

void Company::print_team_salary(int team_id)
{
    Team* founded_team = find_team_by_id(team_id);
    if(founded_team != NULL)
        founded_team->print_salary();
    else
        print_message("TEAM_NOT_FOUND");
}

void Company::print_days_total_working_hours(vector <int> days, vector <int>& days_total_hours)
{
    int total_hours;
    for(int i = 0; i < days.size(); i++)
    {
        total_hours = 0;
        for(Employee* employee : employees)
            total_hours += employee->get_day_hours(days[i]);
        cout << "Day #" << days[i] << ": " << total_hours << endl;
        days_total_hours.push_back(total_hours);
    }
    print_line_separator();
}

string Company::find_days_by_border(vector <int> days_to_be_reported,
                                    vector <int> days_total_hours, int border_val)
{
    string days_with_max_working_hours;
    for(int i = 0; i < days_to_be_reported.size(); i++)
        if(days_total_hours[i] == border_val)
            days_with_max_working_hours += SPACE + to_string(days_to_be_reported[i]);
    return days_with_max_working_hours;
}

void Company::print_days_with_borders(vector <int> days_to_be_reported,
                                      vector <int> days_total_hours , string border_mode)
{
    int border_val;

    if(border_mode == MAX)
        border_val = find_max(days_total_hours);
    else if(border_mode == MIN)
        border_val = find_min(days_total_hours);
    string days_with_border_working_hours = find_days_by_border(days_to_be_reported,
                                                                days_total_hours, border_val);                                                               
    if(border_mode == MAX)
        cout << "Day(s) with Max Working Hours:" << days_with_border_working_hours << endl;
    else if(border_mode == MIN)
        cout << "Day(s) with Min Working Hours:" << days_with_border_working_hours << endl;
}

void Company::report_day_total_hours(int start_day, int end_day)
{
    if(!is_valid_times(start_day, end_day, FIRST_DAY, LAST_DAY))
    {
        print_message("INVALID_ARGUMENTS");
        return;
    }
    vector <int> days_to_be_reported = give_numbers_in_interval(start_day, end_day);
    vector <int> days_total_hours;
    print_days_total_working_hours(days_to_be_reported, days_total_hours);
    print_days_with_borders(days_to_be_reported, days_total_hours, MAX);
    print_days_with_borders(days_to_be_reported, days_total_hours, MIN);
}

string Company::find_avgs_by_border(vector <int> hours_to_be_reported,
                                    vector <float> averages, float border_val)
{
    string hours_with_border_avgs;
    for(int i = 0; i < hours_to_be_reported.size()-1; i++)
    {
        if(averages[i] == border_val)
        {
            hours_with_border_avgs += SPACE + to_string(hours_to_be_reported[i]) + DASH;
            hours_with_border_avgs += to_string(hours_to_be_reported[i+1]);
        }
    }
    return hours_with_border_avgs;
}

void Company::print_avereges_by_border(vector <int> hours_to_be_reported,
                                       vector <float> averages, string border_mode)
{
    float border_val;

    if(border_mode == MAX)
        border_val = find_max(averages);
    else if(border_mode == MIN)
        border_val = find_min(averages);
    string hours_with_border_avgs = find_avgs_by_border(hours_to_be_reported,
                                                        averages, border_val);                                                               
    if(border_mode == MAX)
        cout << "Period(s) with Max Working Employees:" << hours_with_border_avgs << endl;
    else if(border_mode == MIN)
        cout << "Period(s) with Min Working Employees:" << hours_with_border_avgs << endl;
}

void Company::print_working_emps_avg(vector <int> hours_to_be_reported, vector <float>& averages)
{
    int num_of_working_employees = 0;
    for(int i = 0; i < hours_to_be_reported.size()-1; i++)
    {
        for(Employee* employee : employees)
            num_of_working_employees += employee->get_num_of_days_work_in_this_hour(hours_to_be_reported[i],
                                                                                    hours_to_be_reported[i+1]);
        float emp_per_hour = calculate_average(num_of_working_employees, DAY_SIZE);
        cout << hours_to_be_reported[i] << DASH << hours_to_be_reported[i+1] << ": ";
        cout << fixed << setprecision(PRECISION) << emp_per_hour << endl;
        averages.push_back(emp_per_hour);
    }
    print_line_separator();
}

void Company::report_employee_per_hour(int start_hour, int end_hour)
{
    if(!is_valid_times(start_hour, end_hour, START_TIME, END_TIME))
    {
        print_message("INVALID_ARGUMENTS");
        return;
    }
    vector <int> hours_to_be_reported = give_numbers_in_interval(start_hour, end_hour);
    vector <float> avereges;
    print_working_emps_avg(hours_to_be_reported, avereges);
    print_avereges_by_border(hours_to_be_reported, avereges, MAX);
    print_avereges_by_border(hours_to_be_reported, avereges, MIN);
}

void Company::show_salary_config(string salary_level)
{
    Salary* founded_sal = find_salary_by_level(salary_level);
    if(founded_sal != NULL)
        founded_sal->print_configs();
    else
        print_message("INVALID_LEVEL");
}

void Company::update_salary_config(string salary_level, string configs)
{
    Salary* founded_sal = find_salary_by_level(salary_level);
    if(founded_sal != NULL)
    {
        founded_sal->update_configs(configs);
        print_message("OK");
    }
    else
        print_message("INVALID_LEVEL");
}

void Company::update_team_bonus(int team_id, int new_bonus)
{
    Team* founded_team = find_team_by_id(team_id);
    if(founded_team != NULL)
        if(founded_team->update_bonus(new_bonus))
            print_message("OK");
        else
            print_message("INVALID_ARGUMENTS");
    else
        print_message("TEAM_NOT_FOUND");
}

void Company::add_employee_work_hour(int emp_id, string working_time_info)
{
    string adding_status;
    Employee* emp_has_new_work_hour = find_employee_by_id(emp_id);
    if(emp_has_new_work_hour != NULL)
    {
        adding_status = emp_has_new_work_hour->add_work_hour(working_time_info);
        print_message(adding_status);
    }
    else
        print_message("EMPLOYEE_NOT_FOUND");
}

void Company::delete_employee_work_hours(int emp_id, int day)
{
    string deleting_status;
    Employee* emp_delete_work_day = find_employee_by_id(emp_id);
    if(emp_delete_work_day != NULL)
    {
        deleting_status = emp_delete_work_day->delete_work_day(day);
        print_message(deleting_status);
    }
    else
        print_message("EMPLOYEE_NOT_FOUND");
}

void Company::find_teams_for_bonus()
{
    vector <Team*> deserved_teams;
    for(Team* team : teams)
        if(team->is_deserve_bonus())
            deserved_teams.push_back(team);
    if(!deserved_teams.size())
    {
        print_message("NO_BONUS_TEAMS");   
        return;
    }
    sort_teams_by_working_hours(deserved_teams);
}

void Company::sort_employees()
{
    employees = sort_employees_by_id(employees);
}

void Company::sort_teams_members()
{
    for(Team* team : teams)
        team->sort_team_members();
}

vector <int> Company::find_teams_ids(vector <Team*> teams)
{
    vector <int> ids;
    for(Team* team : teams)
        ids.push_back(team->get_team_id());
    return ids;
}

void Company::sort_teams_by_id(vector <int> team_ids, vector <Team*> unsorted_teams)
{
    for(int j = 0; j < team_ids.size(); j++)
    {
        for(int i = 0; i < unsorted_teams.size(); i++)
        {
            if(unsorted_teams[i]->is_id_match(team_ids[j]))
            {
                cout << "Team ID: " << unsorted_teams[i]->get_team_id() << endl; 
                break;
            }
        } 
    }
}

void Company::print_deserved_teams(vector <Team*> unsorted_teams)
{
    vector <int> team_ids = find_teams_ids(unsorted_teams);
    sort(team_ids.begin(), team_ids.end());
    sort_teams_by_id(team_ids, unsorted_teams);
}

void Company::sort_teams_by_working_hours(vector <Team*> deserved_teams)
{
    vector <int> teams_total_working_hours;
    vector <Team*> sorted_teams;

    for(Team* team : deserved_teams)
        teams_total_working_hours.push_back(team->get_total_hour());
    sort(teams_total_working_hours.begin(), teams_total_working_hours.end(), greater<int>());

    for(int j = 0; j < teams_total_working_hours.size(); j++)
    {
        for(int i = 0; i < deserved_teams.size(); i++)
        {
            if(deserved_teams[i]->is_time_match(teams_total_working_hours[j]))
                sorted_teams.push_back(deserved_teams[i]);
        }
        print_deserved_teams(sorted_teams);
        sorted_teams.clear(); 
    }
}

vector <string> read_csv(string filename)
{
    ifstream input_csv(filename);
    string line;
    getline(input_csv, line);
    vector <string> csv_data;

    while(getline(input_csv, line))
        csv_data.push_back(line);

    return csv_data;
}

Company set_employee_data(stringstream& info, Company company)
{
    string name, level;
    int id, age;

    info >> id >> name >> age >> level;
    company.add_employee(id, name, age, level);
    return company;
}

Company set_salary_data(stringstream& info, Company company)
{
    string level;
    int base_sal, sal, sal_extra, work_hours, tax;

    info >> level >> base_sal >> sal >> sal_extra >> work_hours >> tax;
    company.config_salary(level, base_sal, sal, sal_extra, work_hours, tax);
    return company;
}

Company set_team_data(stringstream& info, Company company)
{
    int id, head_id;
    string member_ids;
    int min_bonus;
    float max_bonus;

    info >> id >> head_id >> member_ids >> min_bonus >> max_bonus;
    company.make_team(id, head_id, member_ids, min_bonus, max_bonus);
    return company;
}

Company set_working_hours_data(stringstream& info, Company company)
{
    int id, day;
    string working_interval;

    info >> id >> day >> working_interval;
    company.set_employee_working_time(id, day, working_interval);
    return company;
}

Company determine_by_filename(string data, string filename, Company company)
{
    stringstream info;
    info = replace_identifire(data, COMMA);

    if(filename == EMPCSV)
        company = set_employee_data(info, company);
    else if(filename == SALCSV)
        company = set_salary_data(info, company);
    else if(filename == TEAMSCSV)
        company = set_team_data(info, company);
    else if(filename == WORKHOURCSV)
        company = set_working_hours_data(info, company);

    return company;
}

Company set_company_data(Company company, string filename)
{
    vector <string> data;
    data = read_csv(filename);
    for(int i = 0; i < data.size(); i++)
    {
        company = determine_by_filename(data[i], filename, company);
    }
    return company;
}

Company set_company_info(Company company)
{
    company = set_company_data(company, EMPCSV);
    company.sort_employees();
    company = set_company_data(company, SALCSV);
    company = set_company_data(company, TEAMSCSV);
    company.sort_teams_members();
    company = set_company_data(company, WORKHOURCSV);
    return company;
}

bool is_cmd_report(string cmd)
{
    return (cmd == REPORT_SALARIES) || (cmd == REPORT_EMP_SAL) ||
           (cmd == REPORT_TEAM_SAL) || (cmd == REPORT_TOTAL_HOURS_PER_DAY) ||
           (cmd == REPORT_EMP_PER_HOUR);
}

void process_reports(Company& company ,string report)
{
    int emp_id, team_id;
    if(report == REPORT_SALARIES)
        company.print_salaries();
    else if (report == REPORT_EMP_SAL)
    {
        cin >> emp_id;
        company.print_employee_salary(emp_id);
    }
    else if(report == REPORT_TEAM_SAL)
    {
        cin >> team_id;
        company.print_team_salary(team_id);
    }
    else if(report == REPORT_TOTAL_HOURS_PER_DAY)
    {
        int start_day, end_day;
        cin >> start_day >> end_day;
        company.report_day_total_hours(start_day, end_day);
    }
    else if(report == REPORT_EMP_PER_HOUR)
    {
        int start_hour, end_hour;
        cin >> start_hour >> end_hour;
        company.report_employee_per_hour(start_hour, end_hour);
    }
}

bool is_cmd_config(string cmd)
{
    return (cmd == SHOW_SAL_CONFIG) || (cmd == UPDATE_SAL_CONFIG) ||
           (cmd == ADD_WORK_HOURS) || (cmd == DELETE_WORK_HOURS) ||
           (cmd == UPDATE_TEAM_BONUS) || (cmd == FIND_TEAMS_FOR_BONUS);
}

void process_config(Company& company, string config)
{
    int emp_id, team_id;
    string sal_level;
    if(config == SHOW_SAL_CONFIG)
    {
        cin >> sal_level;
        company.show_salary_config(sal_level);
    }
    else if(config == UPDATE_SAL_CONFIG)
    {
        cin >> sal_level;
        string configs;
        getline(cin, configs);
        company.update_salary_config(sal_level, configs);
    }
    else if(config == ADD_WORK_HOURS)
    {
        cin >> emp_id;
        string working_time_info;
        getline(cin, working_time_info);
        company.add_employee_work_hour(emp_id, working_time_info);
    }
    else if(config == DELETE_WORK_HOURS)
    {
        int day;
        cin >> emp_id;
        cin >> day;
        company.delete_employee_work_hours(emp_id, day);
    }
    else if(config == UPDATE_TEAM_BONUS)
    {
        int new_bonus;
        cin >> team_id >> new_bonus;
        company.update_team_bonus(team_id, new_bonus);
    }
    else if(config == FIND_TEAMS_FOR_BONUS)
        company.find_teams_for_bonus();
}

void process_command(Company& company)
{
    string command;
    int emp_id, team_id;
    while(cin >> command)
    {
        if(is_cmd_report(command))
            process_reports(company, command);
        else if(is_cmd_config(command))
            process_config(company, command);
    }
}

int main()
{
    Company company;
    company = set_company_info(company);
    process_command(company);
    return 0;
}