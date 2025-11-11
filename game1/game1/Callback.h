#pragma once


template <class T1=void, class T2=void, class T3=void>
class GenericCallback
{
public:
	virtual void execute(T1 t1, T2 t2, T3 t3) = 0;
	virtual bool isValid() const = 0;
};
template <class T1, class T2>
class GenericCallback<T1, T2, void>
{
public:
	virtual void execute(T1 t1, T2 t2) = 0;
	virtual bool isValid() const = 0;
};
template <class T1>
class GenericCallback<T1, void, void>
{
public:
	virtual void execute(T1 t1) = 0;
	virtual bool isValid() const = 0;
};
template <>
class GenericCallback<void, void, void>
{
public:
	virtual void execute() = 0;
	virtual bool isValid() const = 0;
};





template <class dest_type, typename T1 = void, typename T2 = void, typename T3 = void>
class Callback : public GenericCallback<T1, T2, T3>
{
public:
	Callback() : objPtr(0), objFuncPtr(0) {}
	~Callback() {}

	Callback(dest_type* objPtr, void (dest_type::* objFuncPtr)(T1, T2, T3)) : objPtr(objPtr), objFuncPtr(objFuncPtr) {}

	virtual void execute(T1 t1, T2 t2, T3 t3) { (objPtr->*objFuncPtr)(t1, t2, t3); }

	virtual bool isValid() const { return (objPtr != 0) && (objFuncPtr != 0); }
private:
	dest_type* objPtr;
	void (dest_type::* objFuncPtr)(T1, T2, T3);
};

template <class dest_type, typename T1, typename T2>
class Callback<dest_type, T1, T2, void> : public GenericCallback<T1, T2>
{
public:
	Callback() : objPtr(0), objFuncPtr(0) {}
	~Callback() {}

	Callback(dest_type* objPtr, void (dest_type::* objFuncPtr)(T1, T2)) : objPtr(objPtr), objFuncPtr(objFuncPtr) {}

	virtual void execute(T1 t1, T2 t2) { (objPtr->*objFuncPtr)(t1, t2); }

	virtual bool isValid() const { return (objPtr != 0) && (objFuncPtr != 0); }
private:
	dest_type* objPtr;
	void (dest_type::* objFuncPtr)(T1, T2);
};

//template <class dest_type, typename T1>
//class Callback : public GenericCallback<T1>
template <class dest_type, typename T1>
class Callback<dest_type, T1, void, void> : public GenericCallback<T1>
{
public:
	Callback() : objPtr(0), objFuncPtr(0) {}
	~Callback() {}

	Callback(dest_type* objPtr, void (dest_type::* objFuncPtr)(T1)) : objPtr(objPtr), objFuncPtr(objFuncPtr) {}

	virtual void execute(T1 t1) { (objPtr->*objFuncPtr)(t1); }

	virtual bool isValid() const { return (objPtr != 0) && (objFuncPtr != 0); }
private:
	dest_type* objPtr;
	void (dest_type::* objFuncPtr)(T1);
};

//template <class dest_type>
//class Callback : public GenericCallback<>
template <class dest_type>
class Callback<dest_type, void, void, void> : public GenericCallback<>
{
public:
	Callback() : objPtr(0), objFuncPtr(0) {}
	~Callback() {}

	Callback(dest_type* objPtr, void (dest_type::* objFuncPtr)()) : objPtr(objPtr), objFuncPtr(objFuncPtr) {}

	virtual void execute() { (objPtr->*objFuncPtr)(); }

	virtual bool isValid() const { return (objPtr != 0) && (objFuncPtr != 0); }
private:
	dest_type* objPtr;
	void (dest_type::* objFuncPtr)();
};
