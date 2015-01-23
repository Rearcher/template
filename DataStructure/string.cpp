#include <stdio.h>
#include <cstring>

//===============================//
/* class String starts from here */
//===============================//

class String
{
public:
	String();
	String(const String &copy);
	String(const char *copy);
	void operator = (const String &copy);
	const char *c_str()const;
protected:
	char *entries;
	int length;
};

String::String()
{
	length = 0;
}

String::String(const String &copy)
{
	length = strlen(copy.entries);
	entries = new char[length+1];
	strcpy(entries, copy.entries);
}

String::String(const char *copy)
{
	length = strlen(copy);
	entries = new char[length+1];
	strcpy(entries, copy);
}

void String::operator = (const String &copy)
{
	length = strlen(copy.entries);
	entries = new char[length+1];
	strcpy(entries, copy.entries);
}

const char* String::c_str()const
{
	return (const char *)entries;
}

//================ ends here ===================//

void strcat(String &add_to, String &add_on)
{
	const char *cfirst = add_to.c_str();
	const char *csecond = add_on.c_str();
	char *copy = new char[strlen(cfirst)+strlen(csecond)+1];
	strcpy(copy, cfirst);
	strcat(copy, csecond);
	add_to = copy;
	delete []copy;
}

void strncpy(String &copy, const String &origin, int n)
{
	char *ans = new char[n+1];
	const char *source = origin.c_str();
	if(n > (int)strlen(source)) return;
	for(int i = 0; i < n; i++)
	{
		ans[i] = source[i];
	}
	copy = ans;
	delete []ans;
}

int strstr(const String &text, const String &target)
{
	const char *content_s = text.c_str();
	char *p = strstr((char *)content_s, target.c_str());
	if(p == NULL)
		return -1;
	else
		return p-content_s;
}

int main()
{
	String a;
	String b("ac");
	strncpy(a,b,1);
	printf("%s\n",a.c_str());
}
