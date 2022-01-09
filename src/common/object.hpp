namespace Common
{
	class Object
	{
	public:
		Object() {};
		virtual ~Object() {};
		
		void init() {};
		virtual void done() {};

		/**
		*	Standard object duplicator.
		*	@returns copy of object
		*/
		virtual Object * clone() const;
		/**
		*	Standard Object comparator.
		*	@param obj object to compare to
		*	@returns 0 for equality, negative number if |this<obj| and positive number if |this>obj|
		*/
		virtual int compareTo(const Object *obj) const;
		/**
		*	Stringify object.
		*	Stringify object in string-buffer <i>s</i>. Never writes more than
		*	<i>maxlen</i> characters to <i>s</i>. If <i>maxlen</i> is > 0, a
		*	trailing zero-character is written.
		*
		*	@param s pointer to buffer that receives object stringification
		*	@param maxlen size of buffer that receives object stringification
		*	@returns number of characters written to <i>s</i>, not including the trailing zero
		*/
		virtual int toString(char *buf, int buflen) const;
		/**
		*	@returns true if <i>this</i> is an object or derived from an object of type <i>id</i>.
		*/
		virtual bool instanceOf(ObjectID id) const;
		/**
		*	@returns true if <i>this</i> is an object or derived from an object of the same type as <i>obj</i>.
		*/
		bool instanceOf(Object *obj) const;
		/**
		*	@returns unique object id.
		*/
		virtual	ObjectID	getObjectID() const;
	};
}