//HASSAN JAWWAD 20L-1122
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
template <typename T>
class node
{
public:
	T data;
	node<T>* next;
	node()
	{
		next = NULL;
	}
	node(T val)
	{
		data = val;
		next = NULL;
	}
	/*void print()
	{
		cout<<data<<" ";
	}*/
	~node()
	{
		next = NULL;
	}
};
class XMLData
{
public:
	int line;
	string tag;
	bool flag;
	XMLData()
	{
		line = 0;
		tag = "";
		flag = 0;
	}
	XMLData(int _line, string _tag, bool _flag)
	{
		line = _line;
		tag = _tag;
		flag = _flag;
	}
	XMLData(const XMLData& obj)
	{
		this->flag = obj.flag;
		this->line = obj.line;
		this->tag = obj.tag;
	}
	void operator = (const XMLData& obj)
	{
		this->flag = obj.flag;
		this->line = obj.line;
		this->tag = obj.tag;
	}
	void print()
	{
		cout << tag << "\t" << line << "\t" << flag << endl;
	}
};
template <typename T>
class stack
{
	node<T>* top;
public:
	stack()
	{
		top = NULL;
	}
	bool isEmpty()
	{
		if (top)
			return 1;
		return 0;
	}
	bool push(const T& val)
	{
		if (top == NULL)
		{
			top = new node<T>(val);
			return 1;
		}
		else
		{
			node<T>* temp = new node<T>(val);
			temp->next = top;
			top = temp;
			return 1;
		}
		return 0;
	}
	bool pop(T& val)
	{
		if (top)
		{
			val = top->data;
			node<T>* temp = top;
			top = top->next;
			delete temp;
			return 1;
		}
		else
			return 0;
	}
	T top1()
	{
		return top->data;
	}
	void print()
	{
		cout << "Current stack: ";
		for (node<T>* temp = top; temp != NULL; temp = temp->next)
			temp->print();
		cout << "\n";
	}
	~stack()
	{
		if (top)
		{
			while (top)
			{
				node<T>* temp = top;
				top = top->next;
				delete temp;
			}
		}
		top = NULL;
	}
};
int main()
{
	stack<XMLData> stack1;
	ifstream file;
	bool OK = true;
	int i = 0, j = 0, k = 0, lineNo = 2;
	file.open("File.xml");
	file.ignore(256, '\n');
	// we are going to read the file character by character till end of file
	if (file)
	{
		while (!file.eof())
		{
			OK = true;
			char temp;
			file.get(temp);
			if (temp == '\n')
				lineNo++;
			string TAG = "";
			//if inverted comma is found then we have to find ending comma before '>' 
			if (temp == '"')
			{
				file.get(temp);
				while (temp != '"')
				{
					if (temp == '>')//if closing commas not found then give error
					{
						cout << "Commas not closed on line " << lineNo << " didn't compile successfully\n";
						break;
					}
					file.get(temp);
				}
			}
			if (temp == '<')//if '<' charactor found then we have to check its starting or ending
			{
				file.get(temp);
				if (temp == '!')//if ! then its comment and we have to ignore till '>' charactor
				{
					OK = false;
					file.get(temp);
					while (temp != '>')
						file.get(temp);
				}
				if (temp != '/' && OK)
				{
					while (temp != ' ' && temp != '\n' && temp != '>')
					{
						TAG += temp;
						file.get(temp);
					}
					XMLData HTML(lineNo, TAG, 1);
					stack1.push(HTML);
				}
				if (temp == '/')//if / found then its closing tag
				{
					file.get(temp);
					while (temp != ' ' && temp != '\n' && temp != '>')
					{
						TAG += temp;
						file.get(temp);
					}
					//after identifying the closing tag we have to peek the stack
					XMLData nikal;
					XMLData HTML(lineNo, TAG, 0);
					XMLData peek = stack1.top1();
					if (HTML.tag == peek.tag && HTML.flag == 0 && peek.flag == 1)//check if it matches with the opening tag then pop it  
						stack1.pop(nikal);
					else//otherwise break execution and give error on screen
						break;
				}
			}
		}
		if (stack1.isEmpty())
		{
			cout << "Stack not empty\nCompilation terminated\n";
			XMLData peek = stack1.top1();
			cout << "Error on line " << lineNo << " " << peek.tag << " tag not closed\n";
		}
		else
			cout << "No tag errors found\n";
	}
	else
		cout << "file not found \n";
	file.close();
	system("PAUSE");
	return 0;
}