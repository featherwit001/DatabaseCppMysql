#include"MysqlConnect.h"
#include<string>
#include<vector>
//#define vector std::vector
//#define string std::string


std::vector<std::string> split(const std::string& str, const std::string& pattern)
{
	std::vector<std::string> res;
	if (str == "")
		return res;
	//在字符串末尾也加入分隔符，方便截取最后一段
	std::string strs = str + pattern;
	size_t pos = strs.find(pattern);

	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		if(temp!="")
			res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(pattern);
	}

	return res;
}
void test()
{
	DataBase* d1 = new DataBase;
	//连接
	d1->Connect("localhost", "root", "root", "s_t_u201911705", 3306);
	printf("\n");
	//查询表
	d1->Query("student");
	printf("\n");
	//添加内容
	d1->Implement("insert into student values('201911222', '赵四','男' ,16, 'CS','否')");

	printf("\n");
	//查询表
	d1->Query("student");
	printf("\n");


	d1->Implement("delete from student where sname='赵四';");
	printf("\n");
	d1->Implement("select * from student;");
	printf("\n");
}
void TestSplit()
{
	std::vector<std::string>  v = split("hello,,,niha,woird,",",");
	int i = v.size();
	if (i++)
	{


	}
}


void PrintMenu()
{
	printf("1.展示选项  2.新生入学信息增加 3.学生信息修改\n");
	printf("4.增加课程 5.修改课程信息 6.删除没有选课的课程信息\n");
	printf("7.录入学生成绩 8.修改学生成绩\n");
	printf("9.按系统计学生的平均成绩、最好成绩、最差成绩、优秀率、不及格人数\n");
	printf("10.按系对学生成绩进行排名，同时显示出学生、课程和成绩信息。\n");
	printf("11.输入学号，显示该学生的基本信息和选课信息。\n");
}

void AddStudent(DataBase* db)
{
	printf("请输入学号，姓名，性别，年龄，学院，奖学金情况：(逗号分隔)\n");
	getchar();
	char para[150];
	std::cin.getline(para, 150);
	std::string input = para;
	std::vector<std::string> splited = split(input, ",");

	char st[150];
	if (splited.size() == 6)
	{
		sprintf_s(st, "insert into student values(%s,%s,%s,%s,%s,%s);",
			splited[0].c_str(), splited[1].c_str(), splited[2].c_str(), splited[3].c_str(), splited[4].c_str(), splited[5].c_str());
		db->Implement(st);
		printf("\n");
		//查询表
		db->Query("student");
		printf("\n");
	}
}

void updateStudent(DataBase* db)
{
	printf("请输入需要修改的学生学号，修改项和修改内容(逗号分隔)\n");
	getchar();
	char para[150];
	std::cin.getline(para, 150);
	std::string input = para;
	std::vector<std::string> splited = split(input, ",");

	char st[150];

	if (splited.size() == 3)
	{
		sprintf_s(st, "update student set %s = %s where Sno = %s ;",
			splited[1].c_str(), splited[2].c_str(), splited[0].c_str());
		db->Implement(st);
		printf("\n");
		//查询表
		db->Query("student");
		printf("\n");
	}
}

void AddCourse(DataBase* db)
{
	printf("请输入需要增加的课程号，课程名，前置课程（可以为NULL）,学分。(逗号分隔)\n");
	getchar();
	char para[150];
	std::cin.getline(para, 150);
	std::string input = para;
	std::vector<std::string> splited = split(input, ",");

	char st[150];

	if (splited.size() == 4)
	{
		sprintf_s(st, "insert into course values(%s,%s,%s,%s);",
			splited[0].c_str(), splited[1].c_str(), splited[2].c_str(), splited[3].c_str());
		db->Implement(st);
		printf("\n");
		//查询表
		db->Query("course");
		printf("\n");
	}
}

void updateCourse(DataBase* db)
{
	printf("请输入需要修改的课程号，修改项和修改内容(逗号分隔)\n");
	getchar();
	char para[150];
	std::cin.getline(para, 150);
	std::string input = para;
	std::vector<std::string> splited = split(input, ",");

	char st[150];

	if (splited.size() == 3)
	{
		sprintf_s(st, "update course set %s = %s where Cno = %s ;",
			splited[1].c_str(), splited[2].c_str(), splited[0].c_str());
		db->Implement(st);
		printf("\n");
		//查询表
		db->Query("course");
		printf("\n");
	}
}

//破坏外键约束
void deleteCoursewithoutStudent(DataBase* db)
{
	printf("是否删除无人选修的课程:1.是, 2.否\n");
	getchar();
	int flag = 0;
	std::cin >> flag;
	char st[]= "SET foreign_key_checks = 0;  delete from course where Cno not in(select Cno from(select distinct c.Cno from sc, course c where sc.Cno = c.Cno) as cc); SET foreign_key_checks = 1;";

	if (flag == 1)
	{
		//sprintf_s(st, "SET foreign_key_checks = 0;  delete from course where Cno not in(select Cno from(select distinct c.Cno from sc, course c where sc.Cno = c.Cno) as cc); SET foreign_key_checks = 1;");
		db->Implement(st);
		db->Query("course");
		printf("\n");
	}

}

void addSC(DataBase* db)
{

	printf("请输入需要增加的学号，课程号，成绩(逗号分隔)\n");
	getchar();
	char para[150];
	std::cin.getline(para, 150);
	std::string input = para;
	std::vector<std::string> splited = split(input, ",");

	char st[150];

	if (splited.size() == 3)
	{
		sprintf_s(st, "insert into sc values(%s,%s,%s);",
			splited[0].c_str(), splited[1].c_str(), splited[2].c_str());
		db->Implement(st);
		printf("\n");
		//查询表
		db->Query("sc");
		printf("\n");
	}

}

void updateSCGrade(DataBase* db)
{
	printf("请输入需要修改的学号和课程号，修改后成绩(逗号分隔)\n");
	getchar();
	char para[150];
	std::cin.getline(para, 150);
	std::string input = para;
	std::vector<std::string> splited = split(input, ",");

	char st[150];

	if (splited.size() == 3)
	{
		sprintf_s(st, "update sc set Grade = %s where Sno = %s and Cno = %s ;",
			splited[2].c_str(), splited[0].c_str(), splited[1].c_str());
		db->Implement(st);
		printf("\n");
		//查询表
		db->Query("sc");
		printf("\n");
	}

}

void deptGrade(DataBase* db)
{
	char st[500];
	sprintf_s(st, "select sdept as dept, ifnull(avg(grade), 0) as \"平均成绩\",ifnull(max(grade), 0) as \"最好成绩\",ifnull(min(grade), 0)as \"最差成绩\",count(grade < 60 or null) as \"不及格人次\",count(grade > 90 or null) / (select count(*)from student a where  a.sdept = dept) as \"优秀率\" from student s left outer join sc on(s.Sno = sc.Sno) GROUP BY dept; ");
	db->Implement(st);
	printf("\n");
	//查询表
	//db->Query("sc");
	//printf("\n");
}


void deptstudentGrade(DataBase* db)
{
	char st[500];
	sprintf_s(st, "create view ssc as select s.Sno as Sno, Sname, Ssex, Sage, Sdept, Scholarship, Cno, Grade from student s left outer join sc on(s.Sno = sc.Sno); select sdept, cname, sname, grade from ssc left outer join course c on ssc.Cno = c.Cno order by sdept, cname, grade desc; drop view ssc;");

	db->Implement("create view ssc as \
select s.Sno as Sno, Sname, Ssex, Sage, Sdept, Scholarship, Cno, Grade \
from student s left outer join sc on(s.Sno = sc.Sno); ");
	db->Implement("select sdept as dept, sname,cname ,grade from ssc left outer join course c on ssc.Cno = c.Cno;");
	db->Implement("drop view ssc;");
	printf("\n");

}

void searchStudent(DataBase* db)
{
	char st[500];
	std::cout << "请输入需要查询的学生学号:\n";
	char usid[30];
	std::cin >> usid;
	sprintf_s(st, "select Sno,Sname,Sdept,Ssex,Cname,Grade from ssc left outer join course c on ssc.Cno = c.Cno where Sno = % s",usid);

	db->Implement("create view ssc as \
select s.Sno as Sno, Sname, Ssex, Sage, Sdept, Scholarship, Cno, Grade \
from student s left outer join sc on(s.Sno = sc.Sno); ");
	db->Implement(st);
	db->Implement("drop view ssc;");
	printf("\n");
}

void Menu()
{
	DataBase* db = new DataBase;
	//连接
	db->Connect("localhost", "root", "root", "exp4", 3306);

	PrintMenu();
	int c = -1;
	while (c != 0)
	{
		printf("输入选项：");
		std::cin >> c;
		if (c == 1)
		{
			PrintMenu();
		}
		else if (c == 2)
		{
			AddStudent(db);
		}
		else if (c == 3)
		{
			updateStudent(db);
		}
		else if (c == 4)
		{
			AddCourse(db);
		}
		else if (c == 5)
		{
			updateCourse(db);
		}
		else if (c == 6)
		{
			deleteCoursewithoutStudent(db);

		}
		else if (c == 7)
		{
			addSC(db);
		}
		else if (c == 8)
		{
			updateSCGrade(db);
		}
		else if (c == 9)
		{
			deptGrade(db);
		}
		else if (c == 10)
		{
			deptstudentGrade(db);
		}
		else if (c == 11)
		{
			searchStudent(db);
		}
	}
	printf("\n谢谢使用,Bye\n");

}






int main()
{
	//test();
	//TestSplit();
	Menu();
	//AddStudent(db);
	return 0;
}
