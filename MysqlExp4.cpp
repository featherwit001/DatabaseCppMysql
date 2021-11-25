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
	//���ַ���ĩβҲ����ָ����������ȡ���һ��
	std::string strs = str + pattern;
	size_t pos = strs.find(pattern);

	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		if(temp!="")
			res.push_back(temp);
		//ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(pattern);
	}

	return res;
}
void test()
{
	DataBase* d1 = new DataBase;
	//����
	d1->Connect("localhost", "root", "root", "s_t_u201911705", 3306);
	printf("\n");
	//��ѯ��
	d1->Query("student");
	printf("\n");
	//�������
	d1->Implement("insert into student values('201911222', '����','��' ,16, 'CS','��')");

	printf("\n");
	//��ѯ��
	d1->Query("student");
	printf("\n");


	d1->Implement("delete from student where sname='����';");
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
	printf("1.չʾѡ��  2.������ѧ��Ϣ���� 3.ѧ����Ϣ�޸�\n");
	printf("4.���ӿγ� 5.�޸Ŀγ���Ϣ 6.ɾ��û��ѡ�εĿγ���Ϣ\n");
	printf("7.¼��ѧ���ɼ� 8.�޸�ѧ���ɼ�\n");
	printf("9.��ϵͳ��ѧ����ƽ���ɼ�����óɼ������ɼ��������ʡ�����������\n");
	printf("10.��ϵ��ѧ���ɼ�����������ͬʱ��ʾ��ѧ�����γ̺ͳɼ���Ϣ��\n");
	printf("11.����ѧ�ţ���ʾ��ѧ���Ļ�����Ϣ��ѡ����Ϣ��\n");
}

void AddStudent(DataBase* db)
{
	printf("������ѧ�ţ��������Ա����䣬ѧԺ����ѧ�������(���ŷָ�)\n");
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
		//��ѯ��
		db->Query("student");
		printf("\n");
	}
}

void updateStudent(DataBase* db)
{
	printf("��������Ҫ�޸ĵ�ѧ��ѧ�ţ��޸�����޸�����(���ŷָ�)\n");
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
		//��ѯ��
		db->Query("student");
		printf("\n");
	}
}

void AddCourse(DataBase* db)
{
	printf("��������Ҫ���ӵĿγ̺ţ��γ�����ǰ�ÿγ̣�����ΪNULL��,ѧ�֡�(���ŷָ�)\n");
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
		//��ѯ��
		db->Query("course");
		printf("\n");
	}
}

void updateCourse(DataBase* db)
{
	printf("��������Ҫ�޸ĵĿγ̺ţ��޸�����޸�����(���ŷָ�)\n");
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
		//��ѯ��
		db->Query("course");
		printf("\n");
	}
}

//�ƻ����Լ��
void deleteCoursewithoutStudent(DataBase* db)
{
	printf("�Ƿ�ɾ������ѡ�޵Ŀγ�:1.��, 2.��\n");
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

	printf("��������Ҫ���ӵ�ѧ�ţ��γ̺ţ��ɼ�(���ŷָ�)\n");
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
		//��ѯ��
		db->Query("sc");
		printf("\n");
	}

}

void updateSCGrade(DataBase* db)
{
	printf("��������Ҫ�޸ĵ�ѧ�źͿγ̺ţ��޸ĺ�ɼ�(���ŷָ�)\n");
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
		//��ѯ��
		db->Query("sc");
		printf("\n");
	}

}

void deptGrade(DataBase* db)
{
	char st[500];
	sprintf_s(st, "select sdept as dept, ifnull(avg(grade), 0) as \"ƽ���ɼ�\",ifnull(max(grade), 0) as \"��óɼ�\",ifnull(min(grade), 0)as \"���ɼ�\",count(grade < 60 or null) as \"�������˴�\",count(grade > 90 or null) / (select count(*)from student a where  a.sdept = dept) as \"������\" from student s left outer join sc on(s.Sno = sc.Sno) GROUP BY dept; ");
	db->Implement(st);
	printf("\n");
	//��ѯ��
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
	std::cout << "��������Ҫ��ѯ��ѧ��ѧ��:\n";
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
	//����
	db->Connect("localhost", "root", "root", "exp4", 3306);

	PrintMenu();
	int c = -1;
	while (c != 0)
	{
		printf("����ѡ�");
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
	printf("\nллʹ��,Bye\n");

}






int main()
{
	//test();
	//TestSplit();
	Menu();
	//AddStudent(db);
	return 0;
}
