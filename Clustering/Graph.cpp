#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<iterator>
using namespace std;
class LinkList
{
	struct node
	{
		double weight=0.0;
		string data="";
		node *next = NULL;
		node *connection = NULL;
	};
	node *head = NULL;
public:
	LinkList()
	{}
	~LinkList()
	{
		delete head;
		head = NULL;
	}
	bool unique_node(string s)
	{
		node *temp = head;
		while (temp != NULL)
		{
			if (temp->data == s)
			{
				return false;
			}
			else
			{
				temp = temp->next;
			}
		}
		return true;
	}
	void add_node(string n)
	{
		if (unique_node(n) == true)
		{
			node *new_node = new node;
			new_node->data = n;
			if (head == NULL)
			{
				head = new_node;
				new_node = NULL;
			}
			else
			{
				node *current = head;
				while (current->next != NULL)
				{
					current = current->next;
				}
				new_node->next = current->next;
				current->next = new_node;
				new_node = NULL;
				current = NULL;
			}
		}
	}
	void connected_edges(string s1, string s2,double d)
	{
		node *current = head;
		node *edge_node = new node;
		edge_node->data = s2;
		edge_node->weight = d;
		if (current->data != s1)
		{
			current = current->next;
		}
		if (current->connection == NULL)
		{
			current->connection = edge_node;
			edge_node = NULL;
		}
		else
		{
			node *temp = current->connection;
			while (temp->connection != NULL)
			{
				temp = temp->connection;
			}
			edge_node->connection = temp->connection;
			temp->connection = edge_node;
			edge_node = NULL;
			temp = NULL;
		}
		current = NULL;
	}
	void print()
	{
		int count = 0;
		node *temp = head;
		while (temp != NULL)
		{
			node *temp1 = temp->connection;
				cout << temp->data;
				count++;
			while (temp1 != NULL)
			{
				cout << "->" << temp1->data << "\n";
	
				temp1 = temp1->connection;
			}
			temp = temp->next;
			cout << "\n";
		}
		cout << "Number of nodes  " << count << "\n";
	}
};
int main()
{
	LinkList l1;
	string s1, s2; double d;
	ifstream in("File.txt");
	while (!in.eof())
	{
		in >> s1;
		l1.add_node(s1);
		in.skipws;
		//in.ignore(100000, '\n');
	}
	in.close();
	in.open("File.txt");
	while (!in.eof())
	{
		in.ignore(9,'	');
		in >> s2;
		l1.add_node(s2);
		in.skipws;
		//in.ignore(100000, '\n');
	}
	in.close();
	in.open("File.txt");
	while (in.eof())
	{
		in.ignore(0);
		in >> s1 >> s2 >> d;
		l1.connected_edges(s1, s2, d);
	}
	l1.print();
	system("pause");
	return 0;
}