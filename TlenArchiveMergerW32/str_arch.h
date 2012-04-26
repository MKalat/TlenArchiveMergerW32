struct CHTDAT 
{
	double time;
	int flags;
	int size;
	int ID;
	int unknown;
	CStringA msg;
};

struct CHTIDX
{
	char name[26];
	char network[6];
	double time;
	int flags;
	int offset;
	int count;
	int ID;
};

struct IDXTMP
{
	int id;
	double time;

};