#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include <string>
#include <typeinfo>

#include <iostream>

namespace Configuration
{
	class Entry
	{
	private:
		bool mandatory;
		bool initialized;
		bool set;
	public:
		Entry(bool mandatory);
		virtual ~Entry();

		bool isSet();
		bool isMandatory();
		bool isInitialized();
		
		virtual std::string getType()
		{
			return "none";
		};
	};
	
	template<class T>
	class TypedEntry : Entry
	{
	private:
		T value;
	public:
		TypedEntry(bool mandatory) : Entry (mandatory) {};
		~TypedEntry()
		{
			//delete this->value;
		};
		
		T getValue()
		{
			return this->value;
		};
		
		void setValue(T value)
		{
			this->value = value;
		};
		
		int	asInt()
		{
			return 0;
		};
		
		std::string asString()
		{
			return "";
		};
		
		virtual std::string getType()
		{
			return typeid(this->value).name();
		};
	};
}

#endif