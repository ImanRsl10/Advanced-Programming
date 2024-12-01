#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const int NUM_OF_CLASSES = 2;
const int NUM_OF_DAYS = 5;
const int NUM_OF_SLOTS = 3;

const string ERROR_MESSAGE = "Not Found";

const string SATURDAY = "Saturday";
const string SUNDAY = "Sunday";
const string MONDAY = "Monday";
const string TUESDAY = "Tuesday";
const string WEDNESDAY = "Wednesday";

const string DAYS[NUM_OF_DAYS] = {SATURDAY, SUNDAY, MONDAY, TUESDAY, WEDNESDAY};

struct Time {
    int hours;
    int minutes;
};

const Time FIRST_SLOT_START = {7,30};
const Time FIRST_SLOT_END = {9,0};
const Time SECOND_SLOT_START = {9,30};
const Time SECOND_SLOT_END = {11,0};
const Time THIRD_SLOT_START = {11,30};
const Time THIRD_SLOT_END = {13,0};

const Time START_TIMES[NUM_OF_SLOTS] = {FIRST_SLOT_START, SECOND_SLOT_START, THIRD_SLOT_START};
const Time END_TIMES[NUM_OF_SLOTS] = {FIRST_SLOT_END, SECOND_SLOT_END, THIRD_SLOT_END};

struct Slot {
    Time start_time;
    Time end_time;
    string course_in_slot;
    string teacher_at_slot;
    bool slot_booked;
};

typedef vector <Slot> Slots;

struct Day {
    string day_name;
    Slots slots;
};

typedef vector <Day> Days;

struct Teacher {
    string teacher_name;
    int num_of_free_days;
    Days free_days;
    int num_of_cources;
    vector <string> courses;
};

struct Course {
    string course_name;
    string _day1;
    string _day2;
    Time start_time;
    Time end_time;
    bool has_teacher;
};

typedef vector <Teacher> Teachers;
typedef vector <Course> Courses;

struct Class {
    Days days;
};

typedef vector <Class> Classes;

vector <string> decode_line()
{
    vector <string> info;
    string line, splitted_line;
    getline(cin >> ws, line);
    stringstream _line(line);

    while(_line >> splitted_line)
        info.push_back(splitted_line);

    return info;
}

Time create_time(string time_str)
{
	Time result;

	result.hours = atoi(time_str.substr(0, 2).c_str());
	result.minutes = atoi(time_str.substr(3).c_str());

	return result;
}

vector <string> slice_vec(vector <string> vec, int m, int n)
{
    auto first = vec.cbegin() + m;
    auto last = vec.cbegin() + n + 1;
    vector <string> sub_vec(first, last);

    return sub_vec;
}                                                                      
                                                         
vector <string> fetch_sized_info(vector <string> splitted_info, int size_of_info)
{
    vector <string> info;
    for(int i = 0; i < size_of_info; i++)
        info.push_back(splitted_info[i]);

    return info;
}

string find_first_by_alphabet(vector <string> names)
{
    sort(names.begin(), names.end());
    return names[0];
}

bool compare_times(Time t1, Time t2)
{
    if(t1.hours >= t2.hours)
        return true;
    else if (t1.hours == t2.hours)
    {
        if(t1.minutes >= t2.minutes)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool compare_strings(string str1, string str2)
{
    if(str1 == str2)
        return true;
    return false;
}

Course save_course_info()
{
    Course new_course;
    vector <string> course_details = decode_line();

    new_course.course_name = course_details[0];
    new_course._day1 = course_details[1];
    new_course._day2 = course_details[2];
    new_course.start_time = create_time(course_details[3]);
    new_course.end_time = create_time(course_details[4]);
    
    return new_course;
}

Slots set_time_slots(Slots slots)
{
    slots.resize(NUM_OF_SLOTS);
    for(int i = 0; i < NUM_OF_SLOTS; i++)
    {
        slots[i].start_time = START_TIMES[i];
        slots[i].end_time = END_TIMES[i];
    }
    return slots;
}

Days set_teacher_days(Days free_days ,vector <string> days, int num_of_free_days)
{
    free_days.resize(num_of_free_days);
    for(int i = 0; i < num_of_free_days; i++)
    {
        free_days[i].day_name = days[i];
        free_days[i].slots = set_time_slots(free_days[i].slots);
    }
    return free_days;
}

Teacher save_teacher_info()
{
    Teacher new_teacher;
    vector <string> teacher_info = decode_line();

    new_teacher.teacher_name = teacher_info[0];
    new_teacher.num_of_free_days = atoi(teacher_info[1].c_str());
    vector <string> free_days = slice_vec(teacher_info, 2, new_teacher.num_of_free_days + 1);
    new_teacher.free_days = set_teacher_days(new_teacher.free_days, free_days, new_teacher.num_of_free_days);
    new_teacher.num_of_cources = atoi(teacher_info[2 + new_teacher.num_of_free_days].c_str());
    vector <string> courses = slice_vec(teacher_info, 3 + new_teacher.num_of_free_days,
                                new_teacher.num_of_free_days + new_teacher.num_of_cources + 2);
    new_teacher.courses = fetch_sized_info(courses, new_teacher.num_of_cources);

    return new_teacher;
}

Courses read_courses_info()
{
    int num_of_courses;
    cin >> num_of_courses;
    Courses courses(num_of_courses);

    for(int _course = 0; _course < num_of_courses; _course++)
        courses[_course] = save_course_info(); 
    
    return courses;
}

Teachers read_teachers_info()
{
    int num_of_teachers;
    cin >> num_of_teachers;
    Teachers teachers(num_of_teachers);

    for(int _teacher = 0; _teacher < num_of_teachers; _teacher++)
        teachers[_teacher] = save_teacher_info(); 
    
    return teachers;
}

bool find_available_courses(Courses courses, Slot current_slot, string current_day_name, Courses& available_courses)
{
    for(int i = 0; i < courses.size(); i++)
    {
        if(courses[i].has_teacher)
            continue;
        if(!(compare_times(current_slot.start_time, courses[i].start_time) &&
                                compare_times(courses[i].end_time, current_slot.end_time)))
            continue;
        if(!compare_strings(current_day_name, courses[i]._day1)) //check course's first day
            continue;
        available_courses.push_back(courses[i]);
    }
    return available_courses.size();
}

bool teacher_slot_has_booked(Teacher teacher, string current_day, int slot_num)
{
    for(int i = 0; i < teacher.num_of_free_days; i++)
        if(teacher.free_days[i].day_name == current_day)
            if(teacher.free_days[i].slots[slot_num].slot_booked == true)
                return true;
    return false;
}

bool teacher_has_course(string course_name, vector <string> teacher_courses)
{
    for(int i = 0; i < teacher_courses.size(); i++)
        if(teacher_courses[i] == course_name)
            return true;
    return false;
}

bool is_in_free_day(string day, Teacher teacher, int slot_num)
{
    for(int i = 0; i < teacher.free_days.size(); i++)
    {
        if(day == teacher.free_days[i].day_name)
            if(!teacher_slot_has_booked(teacher, day, slot_num))
                return true;
    }
    return false;
}

bool find_available_teachers(Course course, Teachers teachers, Teachers& available_teachers,
                             string current_day, int slot_num)
{
    for(int j = 0; j < teachers.size(); j++)
    {
        if(!teacher_has_course(course.course_name, teachers[j].courses))
            continue;
        if(!is_in_free_day(course._day1, teachers[j], slot_num))
            continue;
        if(!is_in_free_day(course._day2, teachers[j], slot_num))
            continue;
        
        available_teachers.push_back(teachers[j]);
    }
    return available_teachers.size();
}

int find_min_num_of_free_days(Teachers available_teachers)
{
    int min_num_day = available_teachers[0].num_of_free_days;
    for(int i = 1; i < available_teachers.size(); i++)
    {
        if(available_teachers[i].num_of_free_days < min_num_day)
            min_num_day = available_teachers[i].num_of_free_days;
    }
    return min_num_day;
}

Teachers find_teachers_with_min_day(Teachers available_teachers, int min_num_of_free_days)
{
    Teachers teachers_with_min_day;

    for(int i = 0; i < available_teachers.size(); i++)
        if(available_teachers[i].num_of_free_days == min_num_of_free_days)
            teachers_with_min_day.push_back(available_teachers[i]);

    return teachers_with_min_day;
}

vector <string> get_teachers_name(Teachers teachers)
{
    vector <string> names;

    for(int i = 0; i < teachers.size(); i++)
        names.push_back(teachers[i].teacher_name);

    return names;
}

Teacher find_teacher_by_name(Teachers teachers, string teacher_name)
{
    Teacher teacher;

    for(int i = 0; i < teachers.size(); i++)
    {
        if(teachers[i].teacher_name == teacher_name)
        {
            teacher = teachers[i];
            break;
        }
    }
    return teacher;
}

Teacher find_the_best_teacher(Teachers available_teachers)
{
    int min_num_of_free_days = find_min_num_of_free_days(available_teachers);
    Teachers teachers_with_min_day = find_teachers_with_min_day(available_teachers, min_num_of_free_days);
    
    if(teachers_with_min_day.size() == 1)
        return teachers_with_min_day[0];
    
    string best_teacher_name = find_first_by_alphabet(get_teachers_name(teachers_with_min_day));
    Teacher best_teacher = find_teacher_by_name(teachers_with_min_day, best_teacher_name);

    return best_teacher;
}

bool course_has_teacher(Teachers teachers, Courses& available_courses, Teachers& specified_teachers, 
                        string current_day, int slot_num)
{
    Teachers available_teachers;

    for(int i = 0; i < available_courses.size(); i++)
    {
        available_teachers.clear();
        if(!find_available_teachers(available_courses[i], teachers, available_teachers, current_day, slot_num))
        {
            available_courses.erase(available_courses.begin() + i);
            i--;
            continue;
        }
        specified_teachers.push_back(find_the_best_teacher(available_teachers));
    }

    return specified_teachers.size();
}

vector <string> get_courses_name(Courses available_courses)
{
    vector <string> names;

    for(int i = 0; i < available_courses.size(); i++)
        names.push_back(available_courses[i].course_name); 

    return names;
}

Course find_course_teacher_by_name(Courses courses, string course_name, Teachers teachers, Teacher& best_teacher)
{
    Course best_course;

    for(int i = 0; i < courses.size(); i++)
    {
        if(courses[i].course_name == course_name)
        {
            best_teacher = teachers[i];
            best_course = courses[i];
            break;
        }
    }
    return best_course;
}

Course find_best_course(Teachers specified_teachers, Courses available_courses, Teacher& best_teacher)
{
    string best_course_name = find_first_by_alphabet(get_courses_name(available_courses));
    Course best_course = find_course_teacher_by_name(available_courses, best_course_name, specified_teachers, best_teacher);

    return best_course;
}

bool find_course(Teachers teachers, Courses courses, Slot current_slot, string current_day_name,
                 int slot_num, Course& best_course, Teacher& best_teacher)
{
    Courses available_courses;
    Teachers specified_teachers;

    if(!find_available_courses(courses, current_slot, current_day_name, available_courses))
        return false;
    if(!course_has_teacher(teachers, available_courses, specified_teachers, current_day_name, slot_num))
        return false;
    if(available_courses.size() == 1 && specified_teachers.size() == 1)
    {
        best_course = available_courses[0];
        best_teacher = specified_teachers[0];
        return true;
    }
    best_course = find_best_course(specified_teachers, available_courses, best_teacher);

    return true;
}

Slot fix_slot(Slot current_slot, Course course, Teacher teacher)
{
    current_slot.course_in_slot = course.course_name;
    current_slot.teacher_at_slot = teacher.teacher_name;
    current_slot.slot_booked = true;

    return current_slot;
}

Courses update_course_status(Courses courses, Course best_course)
{
    for(int i = 0; i < courses.size(); i++)
    {
        if(courses[i].course_name == best_course.course_name)
        {
            courses[i].has_teacher = true;
            break;
        }
    }
    return courses;
}

Teacher fix_days_slots(Teacher teacher, string first_day, string second_day, int slot_num)
{
    for(int i = 0; i < teacher.free_days.size(); i++)
    {
        if(teacher.free_days[i].day_name == first_day)
            teacher.free_days[i].slots[slot_num].slot_booked = true;
        if(teacher.free_days[i].day_name == second_day)
            teacher.free_days[i].slots[slot_num].slot_booked = true;
    }
    return teacher;
}

int map_day_to_num(string day_name)
{
    int day_num = -1;

    for(int i = 0; i < NUM_OF_DAYS; i++)
        if(DAYS[i] == day_name)
            day_num = i;
    
    return day_num;
}

void fix_the_other_day(Days& days, int slot_num, Course course, Teacher teacher)
{
    int the_other_day = map_day_to_num(course._day2);

    days[the_other_day].slots[slot_num].course_in_slot = course.course_name;
    days[the_other_day].slots[slot_num].teacher_at_slot = teacher.teacher_name;
    days[the_other_day].slots[slot_num].slot_booked = true;
}

Teachers update_teacher_status(Teachers teachers, Teacher best_teacher, Course best_course, int slot_num)
{
    for(int i = 0; i < teachers.size(); i++)
    {
        if(teachers[i].teacher_name == best_teacher.teacher_name)
        {
            teachers[i] = fix_days_slots(teachers[i], best_course._day1, best_course._day2, slot_num);
            break;
        }
    }
    return teachers;
}

void update_status(Courses& courses, Teachers& teachers, Course best_course,
                   Teacher best_teacher, Days week_days, int slot_num)
{
    courses = update_course_status(courses, best_course);
    teachers = update_teacher_status(teachers, best_teacher, best_course, slot_num);
}

Slot fix_course_in_slot(Teachers& teachers, Courses& courses, Slot current_slot,
                string current_day_name, Days& week_days, int slot_num)
{
    Courses available_courses;
    Teachers available_teachers;
    Course best_course;
    Teacher best_teacher;
    if(!find_course(teachers, courses, current_slot, current_day_name, slot_num, best_course, best_teacher))
    {
        current_slot.slot_booked = false;
        return current_slot;
    }
    current_slot = fix_slot(current_slot, best_course, best_teacher);
    fix_the_other_day(week_days, slot_num, best_course, best_teacher);
    update_status(courses, teachers, best_course, best_teacher, week_days, slot_num);

    return current_slot;
}

Day set_day(Teachers& teachers, Courses& courses, Day current_day, Days& week_days)
{
    for(int slot_num = 0; slot_num < NUM_OF_SLOTS; slot_num++)
    {
        if(current_day.slots[slot_num].slot_booked)
            continue;
        current_day.slots[slot_num] = fix_course_in_slot(teachers, courses, current_day.slots[slot_num],
                                                         current_day.day_name, week_days, slot_num);
    }

    return current_day;
}

Class set_slot_times(Class one_class)
{
    for(int i = 0; i < NUM_OF_DAYS; i++)
        one_class.days[i].slots = set_time_slots(one_class.days[i].slots);

    return one_class;
}

Class set_days_name(Class one_class)
{
    for(int i = 0; i < NUM_OF_DAYS; i++)
        one_class.days[i].day_name = DAYS[i];

    return one_class; 
}

Class set_days(Teachers& teachers, Courses& courses)
{
    Class one_class;

    one_class.days.resize(NUM_OF_DAYS);
    one_class = set_days_name(one_class);
    one_class = set_slot_times(one_class);

    for (int i = 0; i < NUM_OF_DAYS; i++)
        one_class.days[i] = set_day(teachers, courses, one_class.days[i], one_class.days); 

    return one_class;
}

Courses course_has_no_teacher(Courses courses)
{
    for(int i = 0; i < courses.size(); i++)
        courses[i].has_teacher = false;
    
    return courses;
}

Classes make_class_Plan(Teachers& teachers, Courses& courses)
{
    Classes classes(NUM_OF_CLASSES);
    for(int i = 0; i < NUM_OF_CLASSES; i++)
    {
        courses = course_has_no_teacher(courses);
        classes[i] = set_days(teachers, courses);
    }
    return classes;
}

void print_error_massage()
{
    cout << ERROR_MESSAGE << endl;
}

string modify_time_format(string str)
{
    str = "0" + str;
    return str;
}

string time_to_str(Time t)
{
    string hour = to_string(t.hours);
    string minutes = to_string(t.minutes);

    if(hour.size() == 1)
        hour = modify_time_format(hour);

    if(minutes == "0")
        minutes = modify_time_format(minutes);
    
    return hour + ":" + minutes;
}

void print_slot_info(Slot slot)
{
    cout << slot.teacher_at_slot << ":" << " ";
    string start_time = time_to_str(slot.start_time);
    string end_time = time_to_str(slot.end_time);
    cout << start_time << " " << end_time << endl;
}

bool browse_slots(string course_name, Slots slots)
{
    for(int i = 0; i < NUM_OF_SLOTS; i++)
    {
        if(slots[i].course_in_slot == course_name)
        {
            print_slot_info(slots[i]);
            return true;
        }
    }
    return false;
}

bool browse_days(string course_name, Days days)
{
    for(int i = 0; i < NUM_OF_DAYS; i++)
        if(browse_slots(course_name, days[i].slots))
            return true;
    return false;
}

void browse_classes(string course_name, Classes classes)
{
    for(int i = 0; i < NUM_OF_CLASSES; i++)
        if(!browse_days(course_name, classes[i].days))
            print_error_massage();
}

void print_plans(Classes classes, Courses courses)
{
    vector <string> course_names;
    course_names = get_courses_name(courses);
    sort(course_names.begin(), course_names.end());
    for(int i = 0; i < course_names.size(); i++)
    {
        cout << course_names[i] << endl;
        browse_classes(course_names[i], classes);
    }
}

int main()
{
    Teachers teachers = read_teachers_info();
    Courses courses = read_courses_info();
    Classes classes = make_class_Plan(teachers, courses);
    print_plans(classes, courses);

    return 0;
}