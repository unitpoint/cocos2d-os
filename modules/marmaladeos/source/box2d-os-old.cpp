#if 0
#include "box2d-os.h"
#include "Box2D\Box2D.h"

using namespace ObjectScript;

namespace Box2dObjectScriptOld {

// =====================================================================
/*
template< class T > struct remove_const          { typedef T type; };
template< class T > struct remove_const<const T> { typedef T type; };

template< class T > struct remove_ref		{ typedef T type; };
template< class T > struct remove_ref<T&>	{ typedef T type; };

template< class T > struct remove_ptr		{ typedef T type; };
template< class T > struct remove_ptr<T*>	{ typedef T type; };

template< class T > struct add_ptr		{ typedef T * type; };
template< class T > struct add_ptr<T*>	{ typedef T * type; };

template< class T > struct plain_type { typedef typename remove_ptr<typename remove_ref<typename remove_const<T>::type>::type>::type type; };
template< class T > struct ptr_type { typedef typename add_ptr<typename plain_type<T>::type>::type type; };
*/
// =====================================================================

template <class T> int getClassId(){ static int id = (int)&id; return id; }
template <class T> int getId(){ static int id = (int)&id; return id; }

template <class T> const char * getClassName();

template <> const char * getClassName<b2BodyDef>(){ return "b2BodyDef"; }
template <> const char * getClassName<b2WheelJointDef>(){ return "b2WheelJointDef"; }
template <> const char * getClassName<b2WeldJointDef>(){ return "b2WeldJointDef"; }
template <> const char * getClassName<b2RopeJointDef>(){ return "b2RopeJointDef"; }
template <> const char * getClassName<b2RevoluteJointDef>(){ return "b2RevoluteJointDef"; }
template <> const char * getClassName<b2PulleyJointDef>(){ return "b2PulleyJointDef"; }
template <> const char * getClassName<b2PrismaticJointDef>(){ return "b2PrismaticJointDef"; }
template <> const char * getClassName<b2MouseJointDef>(){ return "b2MouseJointDef"; }
template <> const char * getClassName<b2GearJointDef>(){ return "b2GearJointDef"; }
template <> const char * getClassName<b2FrictionJointDef>(){ return "b2FrictionJointDef"; }
template <> const char * getClassName<b2DistanceJointDef>(){ return "b2DistanceJointDef"; }
template <> const char * getClassName<b2CircleShape>(){ return "b2CircleShape"; }
template <> const char * getClassName<b2FixtureDef>(){ return "b2FixtureDef"; }
template <> const char * getClassName<b2Fixture>(){ return "b2Fixture"; }
template <> const char * getClassName<b2Contact>(){ return "b2Contact"; }
template <> const char * getClassName<b2Body>(){ return "b2Body"; }
template <> const char * getClassName<b2WheelJoint>(){ return "b2WheelJoint"; }
template <> const char * getClassName<b2WeldJoint>(){ return "b2WeldJoint"; }
template <> const char * getClassName<b2JointEdge>(){ return "b2JointEdge"; }
template <> const char * getClassName<b2ContactEdge>(){ return "b2ContactEdge"; }
template <> const char * getClassName<b2RopeJoint>(){ return "b2RopeJoint"; }
template <> const char * getClassName<b2RevoluteJoint>(){ return "b2RevoluteJoint"; }
template <> const char * getClassName<b2PulleyJoint>(){ return "b2PulleyJoint"; }
template <> const char * getClassName<b2PrismaticJoint>(){ return "b2PrismaticJoint"; }
template <> const char * getClassName<b2MouseJoint>(){ return "b2MouseJoint"; }
template <> const char * getClassName<b2GearJoint>(){ return "b2GearJoint"; }
template <> const char * getClassName<b2FrictionJoint>(){ return "b2FrictionJoint"; }
template <> const char * getClassName<b2DistanceJoint>(){ return "b2DistanceJoint"; }
template <> const char * getClassName<b2ManifoldPoint>(){ return "b2ManifoldPoint"; }
template <> const char * getClassName<b2MassData>(){ return "b2MassData"; }
template <> const char * getClassName<b2Manifold>(){ return "b2Manifold"; }
template <> const char * getClassName<b2Shape>(){ return "b2Shape"; }
template <> const char * getClassName<b2ContactImpulse>(){ return "b2ContactImpulse"; }

// template <> const char * getClassName<b2Joint>(){ return "b2Joint"; }

// =====================================================================

b2Vec2 toVec2(OS * os, int offs)
{
	if(os->isObject(offs)){
		os->getProperty(offs, "x");
		float x = os->popNumber();
		
		os->getProperty(offs, "y");
		float y = os->popNumber();

		return b2Vec2(x, y);
	}else if(os->isArray(offs)){
		os->pushStackValue(offs);
		os->pushNumber(0);
		os->getProperty();
		float x = os->popNumber();
		
		os->pushStackValue(offs);
		os->pushNumber(1);
		os->getProperty();
		float y = os->popNumber();

		return b2Vec2(x, y);
	}
	// TODO: trigger error???
	return b2Vec2(0, 0);
}

b2Filter toFilter(OS * os, int offs)
{
	b2Filter filter;
	if(os->isObject(offs)){
		os->getProperty(offs, "categoryBits");
		filter.categoryBits = (uint16)os->popInt();
		
		os->getProperty(offs, "maskBits");
		filter.maskBits = (uint16)os->popInt();
		
		os->getProperty(offs, "groupIndex");
		filter.groupIndex = (uint16)os->popInt();

		return filter;
	}
	// TODO: trigger error???
	filter.categoryBits = 0;
	filter.maskBits = 0;
	filter.groupIndex = 0;
	return filter;
}

b2Transform toTransform(OS * os, int offs)
{
	if(os->isObject(offs)){
		os->getProperty(offs, "x");
		OS_NUMBER x = os->popNumber();
		
		os->getProperty(offs, "y");
		OS_NUMBER y = os->popNumber();
		
		os->getProperty(offs, "angle");
		OS_NUMBER angle = os->popNumber();

		return b2Transform(b2Vec2(x, y), b2Rot(angle));
	}
	// TODO: trigger error???
	return b2Transform(b2Vec2(0, 0), b2Rot(0));
}

b2Color toColor(OS * os, int offs)
{
	if(os->isObject(offs)){
		os->getProperty(offs, "r");
		float r = os->popFloat(1.0f);
		
		os->getProperty(offs, "g");
		float g = os->popFloat(1.0f);

		os->getProperty(offs, "b");
		float b = os->popFloat(1.0f);

		return b2Color(r, g, b);
	}else if(os->isArray(offs)){
		os->pushStackValue(offs);
		os->pushNumber(0);
		os->getProperty();
		float r = os->popFloat(1.0f);
		
		os->pushStackValue(offs);
		os->pushNumber(1);
		os->getProperty();
		float g = os->popFloat(1.0f);

		os->pushStackValue(offs);
		os->pushNumber(2);
		os->getProperty();
		float b = os->popFloat(1.0f);

		return b2Color(r, g, b);
	}
	// TODO: trigger error???
	return b2Color(1, 1, 1);
}

// =====================================================================

template <class T> 
struct ToValue
{
	typedef T type;
};

/* template <class T> 
struct ToValue <const T*>
{
	typedef T * type;
}; */

template <> 
struct ToValue <const b2Vec2&>
{
	typedef b2Vec2 type;
};

template <> 
struct ToValue <const b2Filter&>
{
	typedef b2Filter type;
};

template <> 
struct ToValue <const b2Transform&>
{
	typedef b2Transform type;
};

template <> 
struct ToValue <const b2Color&>
{
	typedef b2Color type;
};

// =====================================================================

template <class T> 
struct PushValue
{
	typedef T type;

	static type arg(T val){ return val; }
};

template <> 
struct PushValue <const b2Vec2&>
{
	typedef b2Vec2 type;

	static type arg(const b2Vec2& val){ return val; }
};

template <> 
struct PushValue <const b2Filter&>
{
	typedef b2Filter type;

	static type arg(const b2Filter& val){ return val; }
};

template <> 
struct PushValue <const b2Transform&>
{
	typedef b2Transform type;

	static type arg(const b2Transform& val){ return val; }
};

template <> 
struct PushValue <const b2Color&>
{
	typedef b2Color type;

	static type arg(const b2Color& val){ return val; }
};

template <class T> 
struct PushValue <const T*>
{
	typedef T * type;

	static type arg(const T * val){ return (T*)val; }
};

/*
template <> 
struct PushValue <b2World*>
{
	typedef World * type;

	static type arg(b2World * val){ return dynamic_cast<World*>(val->GetUse); }
};
*/

// =====================================================================

template <class T> T toValue(OS * os, int offs)
{
	return (T)os->toNumber(offs);
}

template <> bool toValue<bool>(OS * os, int offs)
{
	return os->toBool(offs);
}

template <> b2Vec2 toValue<b2Vec2>(OS * os, int offs)
{
	return toVec2(os, offs);
}

template <> b2Filter toValue<b2Filter>(OS * os, int offs)
{
	return toFilter(os, offs);
}

template <> b2Transform toValue<b2Transform>(OS * os, int offs)
{
	return toTransform(os, offs);
}

template <> b2Color toValue<b2Color>(OS * os, int offs)
{
	return toColor(os, offs);
}

// =====================================================================

template <class T> void pushValue(OS * os, T val)
{
	os->pushNumber(val);
}

template <> void pushValue<bool>(OS * os, bool val)
{
	os->pushBool(val);
}

// =====================================================================

template <class T> void osProxiDestructor(OS * os, void * data, void * user_param)
{
}

template <> void osProxiDestructor<b2Body>(OS * os, void * data, void * user_param)
{
	b2Body * body = (b2Body*)data;
	if(body){
		body->GetWorld()->DestroyBody(body);
	}
}

void osJointDestructor(OS * os, void * data, void * user_param)
{
	b2Joint * joint = (b2Joint*)data;
	if(joint){
		b2Body * body = joint->GetBodyA();
		if(body || (body = joint->GetBodyB())){
			body->GetWorld()->DestroyJoint(joint);
		}else{
			OS_ASSERT(false);
		}
	}
}

template <> void osProxiDestructor<b2Joint>(OS * os, void * data, void * user_param)
{
	osJointDestructor(os, data, user_param);
}

// =====================================================================

#define TO_STR(t) #t

template <class T, class FieldType, FieldType T::*FieldPtr> 
int setField(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		data->*FieldPtr = toValue<typename ToValue<FieldType>::type>(os, -params);
	}
	return 0;
}

template <class T, class FieldType, class T2, FieldType T2::*FieldPtr> 
int setFieldSpec(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		data->*FieldPtr = toValue<typename ToValue<FieldType>::type>(os, -params);
	}
	return 0;
}

template <class T, class FieldType, FieldType T::*FieldPtr> 
int setFieldReadonly(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		os->triggerError(OS_E_ERROR, "Property \"" TO_STR(FieldPtr) "\" is readonly");
	}
	return 0;
}

template <class T, typename FieldType, FieldType T::*FieldPtr> 
int getField(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, PushValue<FieldType>::arg(data->*FieldPtr));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, class T2, FieldType T2::*FieldPtr> 
int getFieldSpec(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, PushValue<FieldType>::arg(data->*FieldPtr));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, void(T::*F)(FieldType)> 
int setFieldByMethod(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		(data->*F)(toValue<typename ToValue<FieldType>::type>(os, -params));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, FieldType(T::*F)()const> 
int getFieldByMethod(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, PushValue<FieldType>::arg((data->*F)()));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, class T2, FieldType(T2::*F)()const> 
int getFieldByMethodSpec(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, PushValue<FieldType>::arg((data->*F)()));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, class T2, FieldType(T2::*F)()> 
int getFieldByNotConstMethodSpec(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, PushValue<FieldType>::arg((data->*F)()));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, typename Arg1Type, FieldType(T::*F)(Arg1Type)> 
int getFieldByNotConstMethodArg1(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, 
			PushValue<FieldType>::arg( (data->*F)(toValue<typename ToValue<Arg1Type>::type>(os, -params)) ));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, typename Arg1Type, FieldType(T::*F)(Arg1Type)const> 
int getFieldByMethodArg1(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, 
			PushValue<FieldType>::arg( (data->*F)(toValue<typename ToValue<Arg1Type>::type>(os, -params)) ));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, typename Arg1Type, typename Arg2Type, FieldType(T::*F)(Arg1Type, Arg2Type)const> 
int getFieldByMethodArgs2(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, 
			PushValue<FieldType>::arg( (data->*F)(
				toValue<typename ToValue<Arg1Type>::type>(os, -params), 
				toValue<typename ToValue<Arg2Type>::type>(os, -params+1)) ));
		return 1;
	}
	return 0;
}

template <class T, typename FieldType, typename Arg1Type, typename Arg2Type, FieldType(T::*F)(Arg1Type, Arg2Type)> 
int getFieldByNotConstMethodArgs2(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, 
			PushValue<FieldType>::arg( (data->*F)(
				toValue<typename ToValue<Arg1Type>::type>(os, -params), 
				toValue<typename ToValue<Arg2Type>::type>(os, -params+1)) ));
		return 1;
	}
	return 0;
}

template <class T, void(T::*F)()> 
int voidMethod(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		(data->*F)();
	}
	return 0;
}

template <class T, typename Arg1Type, void(T::*F)(Arg1Type)> 
int voidMethodArg1(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		(data->*F)(toValue<typename ToValue<Arg1Type>::type>(os, -params));
	}
	return 0;
}

template <class T, typename Arg1Type, typename Arg2Type, void(T::*F)(Arg1Type, Arg2Type)> 
int voidMethodArgs2(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		(data->*F)(toValue<typename ToValue<Arg1Type>::type>(os, -params), toValue<typename ToValue<Arg2Type>::type>(os, -params+1));
	}
	return 0;
}

template <class T, typename Arg1Type, typename Arg2Type, typename Arg3Type, void(T::*F)(Arg1Type, Arg2Type, Arg3Type)> 
int voidMethodArgs3(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		(data->*F)(
			toValue<typename ToValue<Arg1Type>::type>(os, -params), 
			toValue<typename ToValue<Arg2Type>::type>(os, -params+1),
			toValue<typename ToValue<Arg3Type>::type>(os, -params+2)
			);
	}
	return 0;
}

template <class T, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, void(T::*F)(Arg1Type, Arg2Type, Arg3Type, Arg4Type)> 
int voidMethodArgs4(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		(data->*F)(
			toValue<typename ToValue<Arg1Type>::type>(os, -params), 
			toValue<typename ToValue<Arg2Type>::type>(os, -params+1),
			toValue<typename ToValue<Arg3Type>::type>(os, -params+2),
			toValue<typename ToValue<Arg4Type>::type>(os, -params+3)
			);
	}
	return 0;
}

template <class T, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, 
	void(T::*F)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)> 
int voidMethodArgs7(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		(data->*F)(
			toValue<typename ToValue<Arg1Type>::type>(os, -params), 
			toValue<typename ToValue<Arg2Type>::type>(os, -params+1),
			toValue<typename ToValue<Arg3Type>::type>(os, -params+2),
			toValue<typename ToValue<Arg4Type>::type>(os, -params+3),
			toValue<typename ToValue<Arg5Type>::type>(os, -params+4),
			toValue<typename ToValue<Arg6Type>::type>(os, -params+5),
			toValue<typename ToValue<Arg7Type>::type>(os, -params+6)
			);
	}
	return 0;
}

template <class T> 
int construct(OS * os, int params, int, int, void*)
{
	T * def = new (os->pushUserdata(getId<T>(), sizeof(T), osProxiDestructor<T>)) T();
	setValueId(os, def);
	// def->userData = (void*)os->getValueId();
	os->pushStackValue();
	os->getGlobal(getClassName<T>());
	OS_ASSERT(os->isUserdata(getClassId<T>(), -1));
	os->setPrototype(getId<T>());
	return 1;
}

#define CONSTRUCT(T)  {"__construct", construct<T>}

#define SET_FIELD(T, FieldType, FieldName)  {"__set@"#FieldName, setField<T, FieldType, & T::FieldName>}
#define SET_FIELD_NAME(T, FieldType, Name, FieldName)  {"__set@"#Name, setField<T, FieldType, & T::FieldName>}

#define GET_FIELD(T, FieldType, FieldName)  {"__get@"#FieldName, getField<T, FieldType, & T::FieldName>}
#define GET_FIELD_NAME(T, FieldType, Name, FieldName)  {"__get@"#Name, getField<T, FieldType, & T::FieldName>}

#define SET_FIELD_SPEC(T, FieldType, T2, FieldName)  {"__set@"#FieldName, setFieldSpec<T, FieldType, T2, & T2::FieldName>}
#define SET_FIELD_NAME_SPEC(T, FieldType, Name, T2, FieldName)  {"__set@"#Name, setFieldSpec<T, FieldType, T2, & T2::FieldName>}

#define GET_FIELD_SPEC(T, FieldType, T2, FieldName)  {"__get@"#FieldName, getFieldSpec<T, FieldType, T2, & T2::FieldName>}
#define GET_FIELD_NAME_SPEC(T, FieldType, Name, T2, FieldName)  {"__get@"#Name, getFieldSpec<T, FieldType, T2, & T2::FieldName>}

#define SET_FIELD_READONLY(T, FieldType, FieldName)  {"__set@"#FieldName, setFieldReadonly<T, FieldType, & T::FieldName>}

#define GET_METHOD(T, FieldType, FieldName, MethodName)  {"__get@"#FieldName, getFieldByMethod<T, FieldType, & T::MethodName>}
#define GET_METHOD_1(T, FieldType, FieldName, MethodName, Arg1Type)  {#FieldName, getFieldByMethodArg1<T, FieldType, Arg1Type, & T::MethodName>}
#define GET_METHOD_1_NOT_CONST(T, FieldType, FieldName, MethodName, Arg1Type)  {#FieldName, getFieldByNotConstMethodArg1<T, FieldType, Arg1Type, & T::MethodName>}
#define GET_METHOD_2(T, FieldType, FieldName, MethodName, Arg1Type, Arg2Type)  {#FieldName, getFieldByMethodArgs2<T, FieldType, Arg1Type, Arg2Type, & T::MethodName>}
#define GET_METHOD_2_NOT_CONST(T, FieldType, FieldName, MethodName, Arg1Type, Arg2Type)  {#FieldName, getFieldByNotConstMethodArgs2<T, FieldType, Arg1Type, Arg2Type, & T::MethodName>}

#define GET_METHOD_SPEC(T, FieldType, FieldName, T2, MethodName)  {"__get@"#FieldName, getFieldByMethodSpec<T, FieldType, T2, & T2::MethodName>}
#define GET_METHOD_SPEC_NOT_CONST(T, FieldType, FieldName, T2, MethodName)  {"__get@"#FieldName, getFieldByNotConstMethodSpec<T, FieldType, T2, & T2::MethodName>}

#define SET_METHOD(T, FieldType, FieldName, MethodName)  {"__set@"#FieldName, setFieldByMethod<T, FieldType, & T::MethodName>}

#define VOID_METHOD(T, Name, MethodName)  {#Name, voidMethod<T, & T::MethodName>}
#define VOID_METHOD_1(T, Name, MethodName, Arg1Type)  {#Name, voidMethodArg1<T, Arg1Type, & T::MethodName>}
#define VOID_METHOD_2(T, Name, MethodName, Arg1Type, Arg2Type)  {#Name, voidMethodArgs2<T, Arg1Type, Arg2Type, & T::MethodName>}
#define VOID_METHOD_3(T, Name, MethodName, Arg1Type, Arg2Type, Arg3Type)  {#Name, voidMethodArgs3<T, Arg1Type, Arg2Type, Arg3Type, & T::MethodName>}
#define VOID_METHOD_4(T, Name, MethodName, Arg1Type, Arg2Type, Arg3Type, Arg4Type)  {#Name, voidMethodArgs4<T, Arg1Type, Arg2Type, Arg3Type, Arg4Type, & T::MethodName>}
#define VOID_METHOD_7(T, Name, MethodName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type) {#Name, voidMethodArgs7<T, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, & T::MethodName>}

#define SYNTHESIZE(T, FieldType, FieldName) \
			SET_FIELD(T, FieldType, FieldName), \
			GET_FIELD(T, FieldType, FieldName)

#define SYNTHESIZE_SPEC(T, FieldType, T2, FieldName) \
			SET_FIELD_SPEC(T, FieldType, T2, FieldName), \
			GET_FIELD_SPEC(T, FieldType, T2, FieldName)

#define SYNTHESIZE_READONLY(T, FieldType, FieldName) \
			SET_FIELD_READONLY(T, FieldType, FieldName), \
			GET_FIELD(T, FieldType, FieldName)

// =====================================================================

template <class T> void clearUserdata(OS * os, T * val)
{
	os->pushValueById((int)val->GetUserData());
	os->clearUserdata(getId<T>());
	os->pop();
}

// =====================================================================

template <class T> int getValueId(OS * os, T * val)
{
	return (int)val->GetUserData();
}

template <class T> void setValueId(OS * os, T * val)
{
	val->SetUserData((void*)os->getValueId());
}

// =====================================================================

template <> int getValueId<b2BodyDef>(OS * os, b2BodyDef * val)
{
	return 0; // (int)val->userData;
}

template <> void setValueId<b2BodyDef>(OS * os, b2BodyDef * val)
{
	// val->userData = (void*)os->getValueId();
}

// =====================================================================

template <> int getValueId<b2Contact>(OS * os, b2Contact * val)
{
	return 0;
}

template <> void setValueId<b2Contact>(OS * os, b2Contact * val)
{
}

// =====================================================================

template <> int getValueId<b2ContactImpulse>(OS * os, b2ContactImpulse * val)
{
	return 0;
}

template <> void setValueId<b2ContactImpulse>(OS * os, b2ContactImpulse * val)
{
}

// =====================================================================

template <> int getValueId<b2Manifold>(OS * os, b2Manifold * val)
{
	return 0;
}

template <> void setValueId<b2Manifold>(OS * os, b2Manifold * val)
{
}

// =====================================================================

template <> int getValueId<b2MassData>(OS * os, b2MassData * val)
{
	return 0;
}

template <> void setValueId<b2MassData>(OS * os, b2MassData * val)
{
}

// =====================================================================

template <> int getValueId<b2JointEdge>(OS * os, b2JointEdge * val)
{
	return 0;
}

template <> void setValueId<b2JointEdge>(OS * os, b2JointEdge * val)
{
}

// =====================================================================

template <> int getValueId<b2ContactEdge>(OS * os, b2ContactEdge * val){ return 0; }
template <> void setValueId<b2ContactEdge>(OS * os, b2ContactEdge * val){}

// =====================================================================

template <> int getValueId<b2ManifoldPoint>(OS * os, b2ManifoldPoint * val){ return 0; }
template <> void setValueId<b2ManifoldPoint>(OS * os, b2ManifoldPoint * val){}

// =====================================================================

template <> int getValueId<b2Shape>(OS * os, b2Shape * val){ return 0; }
template <> void setValueId<b2Shape>(OS * os, b2Shape * val){}

// =====================================================================

template <class T> void pushObject(OS * os, T * val)
{
	int valueId = getValueId(os, val);
	if(valueId){
		os->pushValueById(valueId);
		if(!os->isNull()){
			OS_ASSERT(os->isUserdata(getId<T>(), -1));
			return;
		}
		os->pop();
	}
	os->pushUserPointer(getId<T>(), val, osProxiDestructor<T>);
	setValueId(os, val);
	os->pushStackValue();
	os->getGlobal(getClassName<T>());
	OS_ASSERT(os->isUserdata(getClassId<T>(), -1));
	os->setPrototype(getId<T>());
}

template <class T> void pushObject(OS * os, const T * val)
{
	pushObject(os, (T*)val);
}

// =====================================================================
/*
template <> void pushObject<const b2ContactImpulse>(OS * os, const b2ContactImpulse * val)
{
	os->pushNull();
}

template <> void pushObject<const b2Manifold>(OS * os, const b2Manifold * val)
{
	os->pushNull();
}
*/
// =====================================================================

template <class T> T * toObject(OS * os, T *& val, int offs)
{
	return val = (T*)os->toUserdata(getId<T>(), offs);
}

template <class T> T * toObject(OS * os, int offs)
{
	return (T*)os->toUserdata(getId<T>(), offs);
}

// =====================================================================

bool toAABB(OS * os, b2AABB& def, int offs)
{
	return false;
}

// =====================================================================

void pushXY(OS * os, const b2Vec2& p)
{
	os->pushNumber(p.x);
	os->pushNumber(p.y);
}

void pushPointAsArray(OS * os, const b2Vec2& p)
{
	os->newArray(2);
	
	os->pushStackValue();
	os->pushNumber(p.x);
	os->addProperty();
				
	os->pushStackValue();
	os->pushNumber(p.y);
	os->addProperty();
}

void pushPointAsObject(OS * os, const b2Vec2& p)
{
	os->newObject();
	
	os->pushStackValue();
	os->pushNumber(p.x);
	os->setProperty("x", false);
				
	os->pushStackValue();
	os->pushNumber(p.y);
	os->setProperty("y", false);
}

void pushFilterAsObject(OS * os, const b2Filter& p)
{
	os->newObject();
	
	os->pushStackValue();
	os->pushNumber(p.categoryBits);
	os->setProperty("categoryBits", false);
				
	os->pushStackValue();
	os->pushNumber(p.maskBits);
	os->setProperty("maskBits", false);
				
	os->pushStackValue();
	os->pushNumber(p.groupIndex);
	os->setProperty("groupIndex", false);
}

void pushColorAsArray(OS * os, const b2Color& color)
{
	os->newArray(3);

	os->pushStackValue();
	os->pushNumber(color.r);
	os->addProperty();

	os->pushStackValue();
	os->pushNumber(color.g);
	os->addProperty();

	os->pushStackValue();
	os->pushNumber(color.b);
	os->addProperty();
}

void pushTransformAsObject(OS * os, const b2Transform& xf)
{
	os->newObject();
	
	os->pushStackValue();
	os->pushNumber(xf.p.x);
	os->setProperty("x", false);
				
	os->pushStackValue();
	os->pushNumber(xf.p.y);
	os->setProperty("y", false);
				
	os->pushStackValue();
	os->pushNumber(xf.q.GetAngle());
	os->setProperty("angle", false);
}

template <> void pushValue<b2Vec2>(OS * os, b2Vec2 val)
{
	pushPointAsObject(os, val);
}

template <> void pushValue<b2Filter>(OS * os, b2Filter val)
{
	pushFilterAsObject(os, val);
}

template <> void pushValue<b2Transform>(OS * os, b2Transform val)
{
	pushTransformAsObject(os, val);
}

template <> void pushValue<b2Color>(OS * os, b2Color val)
{
	pushColorAsArray(os, val);
}

void pushVertices(OS * os, const b2Vec2* vertices, int vertexCount)
{
	os->newArray(vertexCount);
	for(int i = 0; i < vertexCount; i++){
		os->pushStackValue();
		pushPointAsArray(os, vertices[i]);
		os->addProperty();
	}
}

/// Profiling data. Times are in milliseconds.
template <> void pushValue<const b2Profile *>(OS * os, const b2Profile * p)
{
	os->newObject();
	OS::NumberDef numbers[] = {
		{"step", p->step},
		{"collide", p->collide},
		{"solve", p->solve},
		{"solveInit", p->solveInit},
		{"solveVelocity", p->solveVelocity},
		{"solvePosition", p->solvePosition},
		{"broadphase", p->broadphase},
		{"solveTOI", p->solveTOI},
		{}
	};
	os->setNumbers(numbers, false);
}

// =====================================================================

class World: public b2World, b2DestructionListener, b2ContactFilter, b2ContactListener, b2Draw, b2QueryCallback, b2RayCastCallback
{
public:

	OS * os;
	int osId; // weak ref to ObjectScript value

	static World * toWorld(b2World * w)
	{
		return (World*)((char*)w - (int)(b2World*)((World*)NULL));
	}

	World(OS * p_os, const b2Vec2& gravity, bool doSleep): b2World(gravity, doSleep)
	{
		os = p_os;
		osId = os->getValueId();
		SetDestructionListener(this);
		SetContactFilter(this);
		SetContactListener(this);
		SetDebugDraw(this);
	}
	~World()
	{
	}

	void pushThis()
	{
		os->pushValueById(osId);
		OS_ASSERT(os->isUserdata(getId<World>(), -1));
	}

	bool getFunction(const char * name)
	{
		pushThis();
		os->pushStackValue();
		os->getProperty(name);
		if(os->isFunction()){
			os->move(-2, -1);
			return true;
		}
		os->pop(2);
		return false;
	}

	/// Called when any joint is about to be destroyed due
	/// to the destruction of one of its attached bodies.
	void SayGoodbye(b2Joint* joint)
	{
		clearUserdata(os, joint);
	}

	/// Called when any fixture is about to be destroyed due
	/// to the destruction of its parent body.
	void SayGoodbye(b2Fixture* fixture)
	{
		clearUserdata(os, fixture);
	}

	/// Return true if contact calculations should be performed between these two shapes.
	/// @warning for performance reasons this is only called when the AABBs begin to overlap.
	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
	{
		if(getFunction("shouldCollide")){
			pushObject(os, fixtureA);
			pushObject(os, fixtureB);
			os->call(2, 1);
			return os->popBool();
		}
		return true;
	}

	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact)
	{ 
		if(getFunction("beginContact")){
			pushObject(os, contact);
			os->call(1, 0);
		}
	}

	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact)
	{ 
		if(getFunction("endContact")){
			pushObject(os, contact);
			os->call(1, 0);
		}
	}

	/// This is called after a contact is updated. This allows you to inspect a
	/// contact before it goes to the solver. If you are careful, you can modify the
	/// contact manifold (e.g. disable contact).
	/// A copy of the old manifold is provided so that you can detect changes.
	/// Note: this is called only for awake bodies.
	/// Note: this is called even when the number of contact points is zero.
	/// Note: this is not called for sensors.
	/// Note: if you set the number of contact points to zero, you will not
	/// get an EndContact callback. However, you may get a BeginContact callback
	/// the next step.
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		if(getFunction("preSolve")){
			pushObject(os, contact);
			pushObject(os, oldManifold);
			os->call(2, 0);
		}
	}

	/// This lets you inspect a contact after the solver is finished. This is useful
	/// for inspecting impulses.
	/// Note: the contact manifold does not include time of impact impulses, which can be
	/// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
	/// in a separate data structure.
	/// Note: this is only called for contacts that are touching, solid, and awake.
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		if(getFunction("postSolve")){
			pushObject(os, contact);
			pushObject(os, impulse);
			os->call(2, 0);
		}
	}

	/// Draw a closed polygon provided in CCW order.
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if(getFunction("drawPolygon")){
			pushVertices(os, vertices, vertexCount);
			pushValue(os, color);
			pushValue(os, false);
			os->call(3, 0);
		}
	}

	/// Draw a solid closed polygon provided in CCW order.
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if(getFunction("drawPolygon")){
			pushVertices(os, vertices, vertexCount);
			pushValue(os, color);
			pushValue(os, true);
			os->call(3, 0);
		}
	}

	/// Draw a circle.
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		if(getFunction("drawCircle")){
			pushXY(os, center);
			os->pushNumber(radius);
			pushValue(os, color);
			pushValue(os, false);
			os->call(5, 0);
		}
	}
	
	/// Draw a solid circle.
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		if(getFunction("drawSolidCircle")){
			pushXY(os, center);
			os->pushNumber(radius);
			pushValue(os, color);
			pushValue(os, true);
			os->call(5, 0);
		}
	}
	
	/// Draw a line segment.
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		if(getFunction("drawSegment")){
			pushXY(os, p1);
			pushXY(os, p2);
			pushValue(os, color);
			os->call(5, 0);
		}
	}

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	void DrawTransform(const b2Transform& xf)
	{
		if(getFunction("drawTransform")){
			pushValue(os, xf);
			os->call(1, 0);
		}
	}

	/// Called for each fixture found in the query AABB.
	/// @return false to terminate the query.
	bool ReportFixture(b2Fixture* fixture)
	{
		OS_ASSERT(os->isFunction());
		os->pushStackValue();
		os->pushNull();
		pushObject(os, fixture);
		os->call(1, 1);
		return os->popBool();
	}

	/// Called for each fixture found in the query. You control how the ray cast
	/// proceeds by returning a float:
	/// return -1: ignore this fixture and continue
	/// return 0: terminate the ray cast
	/// return fraction: clip the ray to this point
	/// return 1: don't clip the ray and continue
	/// @param fixture the fixture hit by the ray
	/// @param point the point of initial intersection
	/// @param normal the normal vector at the point of intersection
	/// @return -1 to filter, 0 to terminate, fraction to clip the ray for
	/// closest hit, 1 to continue
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
									const b2Vec2& normal, float32 fraction)
	{
		OS_ASSERT(os->isFunction());
		os->pushStackValue();
		os->pushNull();
		pushObject(os, fixture);
		pushXY(os, point);
		pushXY(os, normal);
		pushValue(os, fraction);
		os->call(6, 1);
		return os->popFloat(1.0f);
	}

	static int createBody(OS * os, int params, int, int, void*)
	{
		World * world;
		b2BodyDef * def;
		if(toObject(os, world, -params-1) && toObject(os, def, -params)){
			pushObject(os, world->CreateBody(def));
			return 1;
		}
		return 0;
	}

	static int destroyBody(OS * os, int params, int, int, void*)
	{
		World * world;
		b2Body * body;
		if(toObject(os, world, -params-1) && toObject(os, body, -params)){
			clearUserdata(os, body);
			world->DestroyBody(body);
		}
		return 0;
	}

	static int createJoint(OS * os, int params, int, int, void*)
	{
		World * world;
		if(world = toObject<World>(os, -params-1)){
			b2JointDef * def;
			if(def = toObject<b2WheelJointDef>(os, -params)){
				pushObject(os, (b2WheelJoint*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2WeldJointDef>(os, -params)){
				pushObject(os, (b2WeldJoint*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2RopeJointDef>(os, -params)){
				pushObject(os, (b2RopeJointDef*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2RevoluteJointDef>(os, -params)){
				pushObject(os, (b2RevoluteJointDef*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2PulleyJointDef>(os, -params)){
				pushObject(os, (b2PulleyJointDef*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2PrismaticJointDef>(os, -params)){
				pushObject(os, (b2PrismaticJointDef*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2MouseJointDef>(os, -params)){
				pushObject(os, (b2MouseJointDef*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2GearJointDef>(os, -params)){
				pushObject(os, (b2GearJointDef*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2FrictionJointDef>(os, -params)){
				pushObject(os, (b2FrictionJointDef*)world->CreateJoint(def));
				return 1;
			}
			if(def = toObject<b2DistanceJointDef>(os, -params)){
				pushObject(os, (b2DistanceJointDef*)world->CreateJoint(def));
				return 1;
			}
		}
		return 0;
	}

	static int destroyJoint(OS * os, int params, int, int, void*)
	{
		World * world;
		b2Joint * joint;
		if(toObject(os, world, -params-1) && toObject(os, joint, -params)){
			clearUserdata(os, joint);
			world->DestroyJoint(joint);
		}
		return 0;
	}

	static int step(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			float timeStep = os->toFloat(-params, 0.1f);
			int velocityIterations = os->toInt(-params+1, 1);
			int positionIterations = os->toInt(-params+2, 1);
			world->Step(timeStep, velocityIterations, positionIterations);
		}
		return 0;
	}

	static int clearForces(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			world->ClearForces();
		}
		return 0;
	}

	static int drawDebugData(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			world->DrawDebugData();
		}
		return 0;
	}

	static int queryAABB(OS * os, int params, int, int, void*)
	{
		b2AABB aabb;
		World * world;
		if(toObject(os, world, -params-1) && toAABB(os, aabb, -params+1)){
			os->pushStackValue(-params); // get it at top of stack for ReportFixture
			world->QueryAABB((World*)world, aabb);
		}
		return 0;
	}

	static int rayCast(OS * os, int params, int, int, void*)
	{
		if(params < 3) return 0;
		World * world;
		if(toObject(os, world, -params-1) && os->isFunction(-params)){
			os->pushStackValue(-params); // get it at top of stack for ReportFixture
			world->RayCast((World*)world, toVec2(os, -params+1), toVec2(os, -params+2));
		}
		return 0;
	}

	static int getBodyList(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			pushObject(os, world->GetBodyList());
			return 1;
		}
		return 0;
	}

	static int getJointList(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			// pushObject(os, world->GetJointList());
			// return 1;
		}
		return 0;
	}

	static int getContactList(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			pushObject(os, world->GetContactList());
			return 1;
		}
		return 0;
	}

	static int setWarmStarting(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			world->SetWarmStarting(os->toBool(-params));
		}
		return 0;
	}

	static int setContinuousPhysics(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			world->SetContinuousPhysics(os->toBool(-params));
		}
		return 0;
	}

	static int setSubStepping(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			world->SetSubStepping(os->toBool(-params));
		}
		return 0;
	}

	static int getProxyCount(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			os->pushNumber(world->GetProxyCount());
			return 1;
		}
		return 0;
	}

	static int getBodyCount(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			os->pushNumber(world->GetBodyCount());
			return 1;
		}
		return 0;
	}

	static int getJointCount(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			os->pushNumber(world->GetJointCount());
			return 1;
		}
		return 0;
	}

	static int getContactCount(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			os->pushNumber(world->GetContactCount());
			return 1;
		}
		return 0;
	}

	static int getTreeHeight(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			os->pushNumber(world->GetTreeHeight());
			return 1;
		}
		return 0;
	}

	static int getTreeBalance(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			os->pushNumber(world->GetTreeBalance());
			return 1;
		}
		return 0;
	}

	static int getTreeQuality(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			os->pushNumber(world->GetTreeQuality());
			return 1;
		}
		return 0;
	}

	static int setGravity(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			world->SetGravity(toVec2(os, -params));
		}
		return 0;
	}

	static int getGravity(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			pushPointAsObject(os, world->GetGravity());
			return 1;
		}
		return 0;
	}

	static int getIsLocked(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			pushValue(os, world->IsLocked());
			return 1;
		}
		return 0;
	}

	static int setAutoClearForces(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			world->SetAutoClearForces(os->toBool(-params));
		}
		return 0;
	}

	static int getAutoClearForces(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			pushValue(os, world->GetAutoClearForces());
			return 1;
		}
		return 0;
	}

	static int getProfile(OS * os, int params, int, int, void*)
	{
		World * world;
		if(toObject(os, world, -params-1)){
			pushValue(os, &world->GetProfile());
			return 1;
		}
		return 0;
	}

	static void destructor(OS * os, void * data, void * user_param)
	{
		World * world = (World*)data;
		world->~World();
	}

	static int create(OS * os, int params, int, int, void*)
	{
		b2Vec2 gravity = params > 0 ? toVec2(os, -params) : b2Vec2(0, -9.8f);
		bool sleep = os->toBool(-params+1, true);
		new (os->pushUserdata(getId<World>(), sizeof(World), destructor)) World(os, gravity, sleep);
		os->retainValueById(os->getValueId());
		os->pushStackValue(-1);
		os->getGlobal("b2World");
		OS_ASSERT(os->isUserdata(getClassId<World>(), -1));
		os->setPrototype(getId<World>());
		return 1;
	}

	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			{"__construct", World::create},
			{"createBody", World::createBody},
			{"destroyBody", World::destroyBody},
			{"createJoint", World::createJoint},
			{"destroyJoint", World::destroyJoint},
			{"step", World::step},
			{"clearForces", World::clearForces},
			{"drawDebugData", World::drawDebugData},
			{"queryAABB", World::queryAABB},
			{"rayCast", World::rayCast},
			{"__get@bodyList", World::getBodyList},
			{"__get@jointList", World::getJointList},
			{"__get@contactList", World::getContactList},
			{"__set@warmStarting", World::setWarmStarting},
			{"__set@continuousPhysics", World::setContinuousPhysics},
			{"__set@subStepping", World::setSubStepping},
			{"__get@proxyCount", World::getProxyCount},
			{"__get@bodyCount", World::getBodyCount},
			{"__get@jointCount", World::getJointCount},
			{"__get@contactCount", World::getContactCount},
			{"__get@treeHeight", World::getTreeHeight},
			{"__get@treeBalance", World::getTreeBalance},
			{"__get@treeQuality", World::getTreeQuality},
			{"__set@gravity", World::setGravity},
			{"__get@gravity", World::getGravity},
			{"__get@isLocked", World::getIsLocked},
			{"__set@autoClearForces", World::setAutoClearForces},
			{"__get@autoClearForces", World::getAutoClearForces},
			{"__get@profile", World::getProfile},
			{}
		};

		OS::NullDef nulls[] = {
			{"shouldCollide"},
			{"beginContact"},
			{"endContact"},
			{"preSolve"},
			{"postSolve"},
			{"drawPolygon"},
			{"drawCircle"},
			{"drawSolidCircle"},
			{"drawSegment"},
			{"drawTransform"},
			{}
		};

		os->pushGlobals();
		os->pushString("b2World");
		os->pushUserdata(getClassId<World>(), 0);
		os->setFuncs(list);
		os->setNulls(nulls);
		os->setProperty();
	}
};

template <> const char * getClassName<World>(){ return "World"; }

template <> b2World* toValue<b2World*>(OS * os, int offs)
{
	World * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2World*>(OS * os, b2World* p_val)
{
	World * val = World::toWorld(p_val);
	pushObject(os, val);
}

template <> int getValueId<World>(OS * os, World * val)
{
	return ((World*)val)->osId;
}

template <> void setValueId<World>(OS * os, World * val)
{
}

// =====================================================================

template <> b2BodyType toValue<b2BodyType>(OS * os, int offs)
{
	OS::String str = os->toString(offs);
	if(str == "static") return b2_staticBody;
	if(str == "kinematic") return b2_kinematicBody;
	// if(str == "dynamic") return b2_dynamicBody;
	return b2_dynamicBody;
}

template <> void pushValue<b2BodyType>(OS * os, b2BodyType val)
{
	switch(val){
	case b2_staticBody:
		os->pushString("static");
		break;
	case b2_kinematicBody:
		os->pushString("kinematic");
		break;
	}
	os->pushString("dynamic");
}

struct BodyDef
{
	/*
	static void destructor(OS * os, void * data, void * user_param)
	{
		b2BodyDef * val = (b2BodyDef*)data;
		val->~b2BodyDef();
	}

	static int create(OS * os, int params, int, int, void*)
	{
		b2BodyDef * def = new (os->pushUserdata(getId<b2BodyDef>(), sizeof(b2BodyDef), destructor)) b2BodyDef();
		def->userData = (void*)os->getValueId();
		os->pushStackValue(-1);
		os->getGlobal("b2BodyDef");
		OS_ASSERT(os->isUserdata(getClassId<b2BodyDef>()));
		os->setPrototype(getId<b2BodyDef>());
		return 1;
	}
	*/

	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			SYNTHESIZE(b2BodyDef, b2BodyType, type),
			SYNTHESIZE(b2BodyDef, b2Vec2, position),
			SYNTHESIZE(b2BodyDef, float, angle),
			SYNTHESIZE(b2BodyDef, b2Vec2, linearVelocity),
			SYNTHESIZE(b2BodyDef, float32, angularVelocity),
			SYNTHESIZE(b2BodyDef, float32, linearDamping),
			SYNTHESIZE(b2BodyDef, float32, angularDamping),
			SYNTHESIZE(b2BodyDef, bool, allowSleep),
			SYNTHESIZE(b2BodyDef, bool, awake),
			SYNTHESIZE(b2BodyDef, bool, fixedRotation),
			SYNTHESIZE(b2BodyDef, bool, bullet),
			SYNTHESIZE(b2BodyDef, bool, active),
			SYNTHESIZE(b2BodyDef, float32, gravityScale),
			CONSTRUCT(b2BodyDef),
			// {"__construct", BodyDef::create},
			{}
		};

		os->pushGlobals();
		os->pushString("b2BodyDef");
		os->pushUserdata(getClassId<b2BodyDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2JointEdge* toValue<b2JointEdge*>(OS * os, int offs)
{
	b2JointEdge * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2JointEdge*>(OS * os, b2JointEdge* val)
{
	pushObject(os, val);
}

struct JointEdge
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			SYNTHESIZE_READONLY(b2JointEdge, b2Body*, other),
			// SYNTHESIZE_READONLY(b2JointEdge, b2Joint*, joint),
			SYNTHESIZE_READONLY(b2JointEdge, b2JointEdge*, prev),
			SYNTHESIZE_READONLY(b2JointEdge, b2JointEdge*, next),
			{}
		};

		os->pushGlobals();
		os->pushString("b2JointEdge");
		os->pushUserdata(getClassId<b2JointEdge>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2ContactEdge* toValue<b2ContactEdge*>(OS * os, int offs)
{
	b2ContactEdge * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2ContactEdge*>(OS * os, b2ContactEdge* val)
{
	pushObject(os, val);
}

struct ContactEdge
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			SYNTHESIZE_READONLY(b2ContactEdge, b2Body*, other),
			SYNTHESIZE_READONLY(b2ContactEdge, b2Contact*, contact),
			SYNTHESIZE_READONLY(b2ContactEdge, b2ContactEdge*, prev),
			SYNTHESIZE_READONLY(b2ContactEdge, b2ContactEdge*, next),
			{}
		};

		os->pushGlobals();
		os->pushString("b2ContactEdge");
		os->pushUserdata(getClassId<b2ContactEdge>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2Contact* toValue<b2Contact*>(OS * os, int offs)
{
	b2Contact * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Contact*>(OS * os, b2Contact* val)
{
	pushObject(os, val);
}

struct Contact
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD(b2Contact, const b2Manifold*, manifold, GetManifold),
			// void GetWorldManifold(b2WorldManifold* worldManifold) const;
			GET_METHOD(b2Contact, bool, isTouching, IsTouching),
			SET_METHOD(b2Contact, bool, isEnabled, SetEnabled),
			GET_METHOD(b2Contact, bool, isEnabled, IsEnabled),
			GET_METHOD(b2Contact, const b2Contact*, next, GetNext),
			GET_METHOD(b2Contact, const b2Fixture*, fixtureA, GetFixtureA),
			GET_METHOD(b2Contact, int32, childIndexB, GetChildIndexB),
			SET_METHOD(b2Contact, float32, friction, SetFriction),
			GET_METHOD(b2Contact, float32, friction, GetFriction),
			VOID_METHOD(b2Contact, resetFriction, ResetFriction),
			SET_METHOD(b2Contact, float32, restitution, SetRestitution),
			GET_METHOD(b2Contact, float32, restitution, GetRestitution),
			VOID_METHOD(b2Contact, resetRestitution, ResetRestitution),
			// virtual void Evaluate(b2Manifold* manifold, const b2Transform& xfA, const b2Transform& xfB) = 0;
			{}
		};

		os->pushGlobals();
		os->pushString("b2Contact");
		os->pushUserdata(getClassId<b2Contact>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2JointType toValue<b2JointType>(OS * os, int offs)
{
	OS::String str = os->toString(offs);
	if(str == "revolute") return e_revoluteJoint;
	if(str == "prismatic") return e_prismaticJoint;
	if(str == "distance") return e_distanceJoint;
	if(str == "pulley") return e_pulleyJoint;
	if(str == "mouse") return e_mouseJoint;
	if(str == "gear") return e_gearJoint;
	if(str == "wheel") return e_wheelJoint;
	if(str == "weld") return e_weldJoint;
	if(str == "friction") return e_frictionJoint;
	if(str == "rope") return e_ropeJoint;
	return e_unknownJoint;
}

template <> void pushValue<b2JointType>(OS * os, b2JointType val)
{
	switch(val){
	case e_revoluteJoint:
		os->pushString("revolute");
		break;
	case e_prismaticJoint:
		os->pushString("prismatic");
		break;
	case e_distanceJoint:
		os->pushString("distance");
		break;
	case e_pulleyJoint:
		os->pushString("pulley");
		break;
	case e_mouseJoint:
		os->pushString("mouse");
		break;
	case e_gearJoint:
		os->pushString("gear");
		break;
	case e_wheelJoint:
		os->pushString("wheel");
		break;
	case e_weldJoint:
		os->pushString("weld");
		break;
	case e_frictionJoint:
		os->pushString("friction");
		break;
	case e_ropeJoint:
		os->pushString("rope");
		break;
	}
	os->pushString("unknown");
}

// =====================================================================

template <> b2WheelJointDef* toValue<b2WheelJointDef*>(OS * os, int offs)
{
	b2WheelJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2WheelJointDef*>(OS * os, b2WheelJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2WheelJointDef>(OS * os, b2WheelJointDef * val){ return 0; }
template <> void setValueId<b2WheelJointDef>(OS * os, b2WheelJointDef * val){}

struct WheelJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2WheelJointDef),
			SYNTHESIZE_SPEC(b2WheelJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2WheelJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2WheelJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2WheelJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2WheelJointDef, b2Vec2, localAnchorA),
			SYNTHESIZE(b2WheelJointDef, b2Vec2, localAnchorB),
			SYNTHESIZE(b2WheelJointDef, b2Vec2, localAxisA),
			SYNTHESIZE(b2WheelJointDef, bool, enableMotor),
			SYNTHESIZE(b2WheelJointDef, float32, maxMotorTorque),
			SYNTHESIZE(b2WheelJointDef, float32, motorSpeed),
			SYNTHESIZE(b2WheelJointDef, float32, frequencyHz),
			SYNTHESIZE(b2WheelJointDef, float32, dampingRatio),
			VOID_METHOD_4(b2WheelJointDef, initialize, Initialize, b2Body*, b2Body*, const b2Vec2&, const b2Vec2&),
			{}
		};

		os->pushGlobals();
		os->pushString("b2WheelJointDef");
		os->pushUserdata(getClassId<b2WheelJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2WheelJoint* toValue<b2WheelJoint*>(OS * os, int offs)
{
	b2WheelJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2WheelJoint*>(OS * os, b2WheelJoint* val)
{
	pushObject(os, val);
}

struct WheelJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2WheelJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2WheelJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2WheelJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2WheelJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2WheelJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2WheelJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2WheelJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2WheelJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2WheelJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2WheelJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2WheelJoint, float32, jointTranslation, GetJointTranslation),
			GET_METHOD(b2WheelJoint, float32, jointSpeed, GetJointSpeed),
			GET_METHOD(b2WheelJoint, bool, isMotorEnabled, IsMotorEnabled),
			SET_METHOD(b2WheelJoint, bool, isMotorEnabled, EnableMotor),
			SET_METHOD(b2WheelJoint, float32, motorSpeed, SetMotorSpeed),
			GET_METHOD(b2WheelJoint, float32, motorSpeed, GetMotorSpeed),
			SET_METHOD(b2WheelJoint, float32, maxMotorTorque, SetMaxMotorTorque),
			GET_METHOD(b2WheelJoint, float32, maxMotorTorque, GetMaxMotorTorque),
			GET_METHOD_1(b2WheelJoint, float32, getMotorTorque, GetMotorTorque, float32),
			SET_METHOD(b2WheelJoint, float32, springFrequencyHz, SetSpringFrequencyHz),
			GET_METHOD(b2WheelJoint, float32, springFrequencyHz, GetSpringFrequencyHz),
			SET_METHOD(b2WheelJoint, float32, springDampingRatio, SetSpringDampingRatio),
			GET_METHOD(b2WheelJoint, float32, springDampingRatio, GetSpringDampingRatio),
			{}
		};

		os->pushGlobals();
		os->pushString("b2WheelJoint");
		os->pushUserdata(getClassId<b2WheelJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2WeldJointDef* toValue<b2WeldJointDef*>(OS * os, int offs)
{
	b2WeldJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2WeldJointDef*>(OS * os, b2WeldJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2WeldJointDef>(OS * os, b2WeldJointDef * val){ return 0; }
template <> void setValueId<b2WeldJointDef>(OS * os, b2WeldJointDef * val){}

struct WeldJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2WeldJointDef),
			SYNTHESIZE_SPEC(b2WeldJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2WeldJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2WeldJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2WeldJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2WeldJointDef, b2Vec2, localAnchorA),
			SYNTHESIZE(b2WeldJointDef, b2Vec2, localAnchorB),
			SYNTHESIZE(b2WeldJointDef, float32, referenceAngle),
			VOID_METHOD_3(b2WeldJointDef, initialize, Initialize, b2Body*, b2Body*, const b2Vec2&),
			{}
		};

		os->pushGlobals();
		os->pushString("b2WeldJointDef");
		os->pushUserdata(getClassId<b2WeldJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2WeldJoint* toValue<b2WeldJoint*>(OS * os, int offs)
{
	b2WeldJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2WeldJoint*>(OS * os, b2WeldJoint* val)
{
	pushObject(os, val);
}

struct WeldJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2WeldJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2WeldJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2WeldJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2WeldJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2WeldJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2WeldJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2WeldJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2WeldJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2WeldJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2WeldJoint, float32, getReactionTorque, GetReactionTorque, float32),
			{}
		};

		os->pushGlobals();
		os->pushString("b2WeldJoint");
		os->pushUserdata(getClassId<b2WeldJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2RopeJointDef* toValue<b2RopeJointDef*>(OS * os, int offs)
{
	b2RopeJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2RopeJointDef*>(OS * os, b2RopeJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2RopeJointDef>(OS * os, b2RopeJointDef * val){ return 0; }
template <> void setValueId<b2RopeJointDef>(OS * os, b2RopeJointDef * val){}

struct RopeJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2RopeJointDef),
			SYNTHESIZE_SPEC(b2RopeJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2RopeJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2RopeJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2RopeJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2RopeJointDef, b2Vec2, localAnchorA),
			SYNTHESIZE(b2RopeJointDef, b2Vec2, localAnchorB),
			SYNTHESIZE(b2RopeJointDef, float32, maxLength),
			{}
		};

		os->pushGlobals();
		os->pushString("b2RopeJointDef");
		os->pushUserdata(getClassId<b2RopeJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2RopeJoint* toValue<b2RopeJoint*>(OS * os, int offs)
{
	b2RopeJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2RopeJoint*>(OS * os, b2RopeJoint* val)
{
	pushObject(os, val);
}

template <> b2LimitState toValue<b2LimitState>(OS * os, int offs)
{
	OS::String str = os->toString(offs);
	if(str == "inactive") return e_inactiveLimit;
	if(str == "atlower") return e_atLowerLimit;
	if(str == "atupper") return e_atUpperLimit;
	return e_equalLimits;
}

template <> void pushValue<b2LimitState>(OS * os, b2LimitState val)
{
	switch(val){
	case e_inactiveLimit:
		os->pushString("inactive");
		break;
	case e_atLowerLimit:
		os->pushString("atlower");
		break;
	case e_atUpperLimit:
		os->pushString("atupper");
		break;
	}
	os->pushString("equal");
}

struct RopeJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2RopeJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2RopeJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2RopeJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2RopeJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2RopeJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2RopeJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2RopeJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2RopeJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2RopeJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2RopeJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2RopeJoint, float32, maxLength, GetMaxLength),
			GET_METHOD(b2RopeJoint, b2LimitState, limitState, GetLimitState),
			{}
		};

		os->pushGlobals();
		os->pushString("b2RopeJoint");
		os->pushUserdata(getClassId<b2RopeJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2RevoluteJointDef* toValue<b2RevoluteJointDef*>(OS * os, int offs)
{
	b2RevoluteJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2RevoluteJointDef*>(OS * os, b2RevoluteJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2RevoluteJointDef>(OS * os, b2RevoluteJointDef * val){ return 0; }
template <> void setValueId<b2RevoluteJointDef>(OS * os, b2RevoluteJointDef * val){}

struct RevoluteJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2RevoluteJointDef),
			SYNTHESIZE_SPEC(b2RevoluteJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2RevoluteJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2RevoluteJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2RevoluteJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2RevoluteJointDef, b2Vec2, localAnchorA),
			SYNTHESIZE(b2RevoluteJointDef, b2Vec2, localAnchorB),
			SYNTHESIZE(b2RevoluteJointDef, float32, referenceAngle),
			SYNTHESIZE(b2RevoluteJointDef, bool, enableLimit),
			SYNTHESIZE(b2RevoluteJointDef, float32, lowerAngle),
			SYNTHESIZE(b2RevoluteJointDef, float32, upperAngle),
			SYNTHESIZE(b2RevoluteJointDef, bool, enableMotor),
			SYNTHESIZE(b2RevoluteJointDef, float32, motorSpeed),
			SYNTHESIZE(b2RevoluteJointDef, float32, maxMotorTorque),
			VOID_METHOD_3(b2RevoluteJointDef, initialize, Initialize, b2Body*, b2Body*, const b2Vec2&),
			{}
		};

		os->pushGlobals();
		os->pushString("b2RevoluteJointDef");
		os->pushUserdata(getClassId<b2RevoluteJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2RevoluteJoint* toValue<b2RevoluteJoint*>(OS * os, int offs)
{
	b2RevoluteJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2RevoluteJoint*>(OS * os, b2RevoluteJoint* val)
{
	pushObject(os, val);
}

struct RevoluteJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2RevoluteJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2RevoluteJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2RevoluteJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2RevoluteJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2RevoluteJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2RevoluteJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2RevoluteJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2RevoluteJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2RevoluteJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2RevoluteJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2RevoluteJoint, float32, jointAngle, GetJointAngle),
			GET_METHOD(b2RevoluteJoint, float32, jointSpeed, GetJointSpeed),
			GET_METHOD(b2RevoluteJoint, bool, isLimitEnabled, IsLimitEnabled),
			SET_METHOD(b2RevoluteJoint, bool, isLimitEnabled, EnableLimit),
			GET_METHOD(b2RevoluteJoint, float32, lowerLimit, GetLowerLimit),
			GET_METHOD(b2RevoluteJoint, float32, upperLimit, GetUpperLimit),
			VOID_METHOD_2(b2RevoluteJoint, setLimits, SetLimits, float32, float32),
			GET_METHOD(b2RevoluteJoint, bool, isMotorEnabled, IsMotorEnabled),
			SET_METHOD(b2RevoluteJoint, bool, isMotorEnabled, EnableMotor),
			SET_METHOD(b2RevoluteJoint, float32, motorSpeed, SetMotorSpeed),
			GET_METHOD(b2RevoluteJoint, float32, motorSpeed, GetMotorSpeed),
			SET_METHOD(b2RevoluteJoint, float32, maxMotorTorque, SetMaxMotorTorque),
			GET_METHOD_1(b2RevoluteJoint, float32, motorTorque, GetMotorTorque, float32),
			{}
		};

		os->pushGlobals();
		os->pushString("b2RevoluteJoint");
		os->pushUserdata(getClassId<b2RevoluteJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2PulleyJointDef* toValue<b2PulleyJointDef*>(OS * os, int offs)
{
	b2PulleyJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2PulleyJointDef*>(OS * os, b2PulleyJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2PulleyJointDef>(OS * os, b2PulleyJointDef * val){ return 0; }
template <> void setValueId<b2PulleyJointDef>(OS * os, b2PulleyJointDef * val){}

struct PulleyJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2PulleyJointDef),
			SYNTHESIZE_SPEC(b2PulleyJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2PulleyJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2PulleyJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2PulleyJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2PulleyJointDef, b2Vec2, localAnchorA),
			SYNTHESIZE(b2PulleyJointDef, b2Vec2, localAnchorB),
			SYNTHESIZE(b2PulleyJointDef, b2Vec2, groundAnchorA),
			SYNTHESIZE(b2PulleyJointDef, b2Vec2, groundAnchorB),
			SYNTHESIZE(b2PulleyJointDef, float32, lengthA),
			SYNTHESIZE(b2PulleyJointDef, float32, lengthB),
			SYNTHESIZE(b2PulleyJointDef, float32, ratio),
			VOID_METHOD_7(b2PulleyJointDef, initialize, Initialize, b2Body*, b2Body*, const b2Vec2&, const b2Vec2&, const b2Vec2&, const b2Vec2&, float32),
			{}
		};

		os->pushGlobals();
		os->pushString("b2PulleyJointDef");
		os->pushUserdata(getClassId<b2PulleyJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2PulleyJoint* toValue<b2PulleyJoint*>(OS * os, int offs)
{
	b2PulleyJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2PulleyJoint*>(OS * os, b2PulleyJoint* val)
{
	pushObject(os, val);
}

struct PulleyJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2PulleyJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2PulleyJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2PulleyJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2PulleyJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2PulleyJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2PulleyJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2PulleyJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2PulleyJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2PulleyJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2PulleyJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2PulleyJoint, b2Vec2, groundAnchorA, GetGroundAnchorA),
			GET_METHOD(b2PulleyJoint, b2Vec2, groundAnchorB, GetGroundAnchorB),
			GET_METHOD(b2PulleyJoint, float32, length1, GetLength1),
			GET_METHOD(b2PulleyJoint, float32, length2, GetLength2),
			GET_METHOD(b2PulleyJoint, float32, ratio, GetRatio),
			{}
		};

		os->pushGlobals();
		os->pushString("b2PulleyJoint");
		os->pushUserdata(getClassId<b2PulleyJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2PrismaticJointDef* toValue<b2PrismaticJointDef*>(OS * os, int offs)
{
	b2PrismaticJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2PrismaticJointDef*>(OS * os, b2PrismaticJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2PrismaticJointDef>(OS * os, b2PrismaticJointDef * val){ return 0; }
template <> void setValueId<b2PrismaticJointDef>(OS * os, b2PrismaticJointDef * val){}

struct PrismaticJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2PrismaticJointDef),
			SYNTHESIZE_SPEC(b2PrismaticJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2PrismaticJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2PrismaticJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2PrismaticJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2PrismaticJointDef, b2Vec2, localAnchorA),
			SYNTHESIZE(b2PrismaticJointDef, b2Vec2, localAnchorB),
			SYNTHESIZE(b2PrismaticJointDef, b2Vec2, localAxisA),
			SYNTHESIZE(b2PrismaticJointDef, float32, referenceAngle),
			SYNTHESIZE(b2PrismaticJointDef, bool, enableLimit),
			SYNTHESIZE(b2PrismaticJointDef, float32, lowerTranslation),
			SYNTHESIZE(b2PrismaticJointDef, float32, upperTranslation),
			SYNTHESIZE(b2PrismaticJointDef, bool, enableMotor),
			SYNTHESIZE(b2PrismaticJointDef, float32, maxMotorForce),
			SYNTHESIZE(b2PrismaticJointDef, float32, motorSpeed),
			VOID_METHOD_4(b2PrismaticJointDef, initialize, Initialize, b2Body*, b2Body*, const b2Vec2&, const b2Vec2&),
			{}
		};

		os->pushGlobals();
		os->pushString("b2PrismaticJointDef");
		os->pushUserdata(getClassId<b2PrismaticJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2PrismaticJoint* toValue<b2PrismaticJoint*>(OS * os, int offs)
{
	return toObject<b2PrismaticJoint>(os, offs);
}

template <> void pushValue<b2PrismaticJoint*>(OS * os, b2PrismaticJoint* val)
{
	pushObject(os, val);
}

struct PrismaticJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2PrismaticJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2PrismaticJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2PrismaticJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2PrismaticJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2PrismaticJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2PrismaticJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2PrismaticJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2PrismaticJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2PrismaticJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2PrismaticJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2PrismaticJoint, float32, jointTranslation, GetJointTranslation),
			GET_METHOD(b2PrismaticJoint, float32, jointSpeed, GetJointSpeed),
			GET_METHOD(b2PrismaticJoint, bool, isLimitEnabled, IsLimitEnabled),
			SET_METHOD(b2PrismaticJoint, bool, isLimitEnabled, EnableLimit),
			GET_METHOD(b2PrismaticJoint, float32, lowerLimit, GetLowerLimit),
			GET_METHOD(b2PrismaticJoint, float32, upperLimit, GetUpperLimit),
			VOID_METHOD_2(b2PrismaticJoint, setLimits, SetLimits, float32, float32),
			GET_METHOD(b2PrismaticJoint, bool, isMotorEnabled, IsMotorEnabled),
			SET_METHOD(b2PrismaticJoint, bool, isMotorEnabled, EnableMotor),
			GET_METHOD(b2PrismaticJoint, float32, motorSpeed, GetMotorSpeed),
			SET_METHOD(b2PrismaticJoint, float32, motorSpeed, SetMotorSpeed),
			SET_METHOD(b2PrismaticJoint, float32, maxMotorForce, SetMaxMotorForce),
			GET_METHOD_1(b2PrismaticJoint, float32, getMotorForce, GetMotorForce, float32),
			{}
		};

		os->pushGlobals();
		os->pushString("b2PrismaticJoint");
		os->pushUserdata(getClassId<b2PrismaticJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2MouseJointDef* toValue<b2MouseJointDef*>(OS * os, int offs)
{
	b2MouseJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2MouseJointDef*>(OS * os, b2MouseJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2MouseJointDef>(OS * os, b2MouseJointDef * val){ return 0; }
template <> void setValueId<b2MouseJointDef>(OS * os, b2MouseJointDef * val){}

struct MouseJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2MouseJointDef),
			SYNTHESIZE_SPEC(b2MouseJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2MouseJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2MouseJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2MouseJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2MouseJointDef, b2Vec2, target),
			SYNTHESIZE(b2MouseJointDef, float32, maxForce),
			SYNTHESIZE(b2MouseJointDef, float32, frequencyHz),
			SYNTHESIZE(b2MouseJointDef, float32, dampingRatio),
			{}
		};

		os->pushGlobals();
		os->pushString("b2MouseJointDef");
		os->pushUserdata(getClassId<b2MouseJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2MouseJoint* toValue<b2MouseJoint*>(OS * os, int offs)
{
	b2MouseJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2MouseJoint*>(OS * os, b2MouseJoint* val)
{
	pushObject(os, val);
}

struct MouseJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2MouseJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2MouseJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2MouseJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2MouseJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2MouseJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2MouseJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2MouseJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2MouseJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2MouseJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2MouseJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2MouseJoint, const b2Vec2&, target, GetTarget),
			SET_METHOD(b2MouseJoint, const b2Vec2&, target, SetTarget),
			GET_METHOD(b2MouseJoint, float32, maxForce, GetMaxForce),
			SET_METHOD(b2MouseJoint, float32, maxForce, SetMaxForce),
			GET_METHOD(b2MouseJoint, float32, frequency, GetFrequency),
			SET_METHOD(b2MouseJoint, float32, frequency, SetFrequency),
			GET_METHOD(b2MouseJoint, float32, dampingRatio, GetDampingRatio),
			SET_METHOD(b2MouseJoint, float32, dampingRatio, SetDampingRatio),
			{}
		};

		os->pushGlobals();
		os->pushString("b2MouseJoint");
		os->pushUserdata(getClassId<b2MouseJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2GearJointDef* toValue<b2GearJointDef*>(OS * os, int offs)
{
	b2GearJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2GearJointDef*>(OS * os, b2GearJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2GearJointDef>(OS * os, b2GearJointDef * val){ return 0; }
template <> void setValueId<b2GearJointDef>(OS * os, b2GearJointDef * val){}

struct GearJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2GearJointDef),
			SYNTHESIZE_SPEC(b2GearJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2GearJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2GearJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2GearJointDef, bool, b2JointDef, collideConnected),
			// SYNTHESIZE(b2GearJointDef, b2Joint*, joint1),
			// SYNTHESIZE(b2GearJointDef, b2Joint*, joint2),
			SYNTHESIZE(b2GearJointDef, float32, ratio),
			{}
		};

		os->pushGlobals();
		os->pushString("b2GearJointDef");
		os->pushUserdata(getClassId<b2GearJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2GearJoint* toValue<b2GearJoint*>(OS * os, int offs)
{
	b2GearJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2GearJoint*>(OS * os, b2GearJoint* val)
{
	pushObject(os, val);
}

struct GearJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2GearJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2GearJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2GearJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2GearJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2GearJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2GearJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2GearJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2GearJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2GearJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2GearJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2GearJoint, float32, ratio, GetRatio),
			SET_METHOD(b2GearJoint, float32, ratio, SetRatio),
			{}
		};

		os->pushGlobals();
		os->pushString("b2GearJoint");
		os->pushUserdata(getClassId<b2GearJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2FrictionJointDef* toValue<b2FrictionJointDef*>(OS * os, int offs)
{
	b2FrictionJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2FrictionJointDef*>(OS * os, b2FrictionJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2FrictionJointDef>(OS * os, b2FrictionJointDef * val){ return 0; }
template <> void setValueId<b2FrictionJointDef>(OS * os, b2FrictionJointDef * val){}

struct FrictionJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2FrictionJointDef),
			SYNTHESIZE_SPEC(b2FrictionJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2FrictionJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2FrictionJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2FrictionJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2FrictionJointDef, b2Vec2, localAnchorA),
			SYNTHESIZE(b2FrictionJointDef, b2Vec2, localAnchorB),
			SYNTHESIZE(b2FrictionJointDef, float32, maxForce),
			SYNTHESIZE(b2FrictionJointDef, float32, maxTorque),
			VOID_METHOD_3(b2FrictionJointDef, initialize, Initialize, b2Body*, b2Body*, const b2Vec2&),
			{}
		};

		os->pushGlobals();
		os->pushString("b2FrictionJointDef");
		os->pushUserdata(getClassId<b2FrictionJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2FrictionJoint* toValue<b2FrictionJoint*>(OS * os, int offs)
{
	b2FrictionJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2FrictionJoint*>(OS * os, b2FrictionJoint* val)
{
	pushObject(os, val);
}

struct FrictionJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2FrictionJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2FrictionJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2FrictionJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2FrictionJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2FrictionJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2FrictionJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2FrictionJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2FrictionJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2FrictionJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2FrictionJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2FrictionJoint, float32, maxForce, GetMaxForce),
			SET_METHOD(b2FrictionJoint, float32, maxForce, SetMaxForce),
			GET_METHOD(b2FrictionJoint, float32, maxTorque, GetMaxTorque),
			SET_METHOD(b2FrictionJoint, float32, maxTorque, SetMaxTorque),
			{}
		};

		os->pushGlobals();
		os->pushString("b2FrictionJoint");
		os->pushUserdata(getClassId<b2FrictionJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2DistanceJointDef* toValue<b2DistanceJointDef*>(OS * os, int offs)
{
	b2DistanceJointDef * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2DistanceJointDef*>(OS * os, b2DistanceJointDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2DistanceJointDef>(OS * os, b2DistanceJointDef * val){ return 0; }
template <> void setValueId<b2DistanceJointDef>(OS * os, b2DistanceJointDef * val){}

struct DistanceJointDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2DistanceJointDef),
			SYNTHESIZE_SPEC(b2DistanceJointDef, b2JointType, b2JointDef, type),
			SYNTHESIZE_SPEC(b2DistanceJointDef, b2Body*, b2JointDef, bodyA),
			SYNTHESIZE_SPEC(b2DistanceJointDef, b2Body*, b2JointDef, bodyB),
			SYNTHESIZE_SPEC(b2DistanceJointDef, bool, b2JointDef, collideConnected),
			SYNTHESIZE(b2DistanceJointDef, b2Vec2, localAnchorA),
			SYNTHESIZE(b2DistanceJointDef, b2Vec2, localAnchorB),
			SYNTHESIZE(b2DistanceJointDef, float32, length),
			SYNTHESIZE(b2DistanceJointDef, float32, frequencyHz),
			SYNTHESIZE(b2DistanceJointDef, float32, dampingRatio),
			VOID_METHOD_4(b2DistanceJointDef, initialize, Initialize, b2Body*, b2Body*, const b2Vec2&, const b2Vec2&),
			{}
		};

		os->pushGlobals();
		os->pushString("b2DistanceJointDef");
		os->pushUserdata(getClassId<b2DistanceJointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2DistanceJoint* toValue<b2DistanceJoint*>(OS * os, int offs)
{
	b2DistanceJoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2DistanceJoint*>(OS * os, b2DistanceJoint* val)
{
	pushObject(os, val);
}

struct DistanceJoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_SPEC(b2DistanceJoint, b2JointType, type, b2Joint, GetType),
			GET_METHOD_SPEC_NOT_CONST(b2DistanceJoint, b2Body*, bodyA, b2Joint, GetBodyA),
			GET_METHOD_SPEC_NOT_CONST(b2DistanceJoint, b2Body*, bodyB, b2Joint, GetBodyB),
			// GET_METHOD_SPEC(b2DistanceJoint, const b2Joint*, next, b2Joint, GetNext),
			GET_METHOD_SPEC(b2DistanceJoint, bool, isActive, b2Joint, IsActive),
			GET_METHOD_SPEC(b2DistanceJoint, bool, collideConnected, b2Joint, GetCollideConnected),

			GET_METHOD(b2DistanceJoint, b2Vec2, anchorA, GetAnchorA),
			GET_METHOD(b2DistanceJoint, b2Vec2, anchorB, GetAnchorB),
			GET_METHOD_1(b2DistanceJoint, b2Vec2, getReactionForce, GetReactionForce, float32),
			GET_METHOD_1(b2DistanceJoint, float32, getReactionTorque, GetReactionTorque, float32),
			GET_METHOD(b2DistanceJoint, float32, length, GetLength),
			SET_METHOD(b2DistanceJoint, float32, length, SetLength),
			GET_METHOD(b2DistanceJoint, float32, frequency, GetFrequency),
			SET_METHOD(b2DistanceJoint, float32, frequency, SetFrequency),
			GET_METHOD(b2DistanceJoint, float32, dampingRatio, GetDampingRatio),
			SET_METHOD(b2DistanceJoint, float32, dampingRatio, SetDampingRatio),
			{}
		};

		os->pushGlobals();
		os->pushString("b2DistanceJoint");
		os->pushUserdata(getClassId<b2DistanceJoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> const b2MassData* toValue<const b2MassData*>(OS * os, int offs)
{
	const b2MassData * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2MassData*>(OS * os, b2MassData* val)
{
	pushObject(os, val);
}

struct MassData
{
	static void destructor(OS * os, void * data, void * user_param)
	{
		b2MassData * val = (b2MassData*)data;
		val->~b2MassData();
	}

	static int create(OS * os, int params, int, int, void*)
	{
		pushDefault(os);
		return 1;
	}

	static b2MassData * pushDefault(OS * os)
	{
		b2MassData * def = new (os->pushUserdata(getId<b2MassData>(), sizeof(b2MassData), destructor)) b2MassData();
		// def->userData = (void*)os->getValueId();
		os->pushStackValue(-1);
		os->getGlobal("b2MassData");
		OS_ASSERT(os->isUserdata(getClassId<b2MassData>(), -1));
		os->setPrototype(getId<b2MassData>());
		return def;
	}

	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			SYNTHESIZE(b2MassData, float32, mass),
			SYNTHESIZE(b2MassData, b2Vec2, center),
			SYNTHESIZE(b2MassData, float32, I),
			{"__construct", MassData::create},
			{}
		};

		os->pushGlobals();
		os->pushString("b2MassData");
		os->pushUserdata(getClassId<b2MassData>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2CircleShape* toValue<b2CircleShape*>(OS * os, int offs)
{
	return toObject<b2CircleShape>(os, offs);
}

template <> void pushValue<b2CircleShape*>(OS * os, b2CircleShape* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2CircleShape>(OS * os, b2CircleShape * val){ return 0; }
template <> void setValueId<b2CircleShape>(OS * os, b2CircleShape * val){}

struct CircleShape
{
	static int computeMass(OS * os, int params, int, int, void*)
	{
		b2CircleShape * shape = toObject<b2CircleShape>(os, -params-1);
		if(shape){
			b2MassData * data = MassData::pushDefault(os);
			shape->ComputeMass(data, toValue<float32>(os, -params));
			// pushValue(os, data); - already in stack
			return 1;
		}
		return 0;
	}

	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2CircleShape),
			GET_METHOD_SPEC(b2CircleShape, b2Shape::Type, type, b2Shape, GetType),
			GET_FIELD_NAME_SPEC(b2CircleShape, float32, radius, b2Shape, m_radius),
			SET_FIELD_NAME_SPEC(b2CircleShape, float32, radius, b2Shape, m_radius),
			GET_FIELD_NAME(b2CircleShape, b2Vec2, position, m_p),
			SET_FIELD_NAME(b2CircleShape, b2Vec2, position, m_p),
			// b2Shape* Clone(b2BlockAllocator* allocator) const;
			GET_METHOD(b2CircleShape, int32, childCount, GetChildCount),
			GET_METHOD_2(b2CircleShape, bool, testPoint, TestPoint, const b2Transform&, const b2Vec2&),
			// bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, const b2Transform& transform, int32 childIndex) const;
			// void ComputeAABB(b2AABB* aabb, const b2Transform& transform, int32 childIndex) const;
			{"computeMass", computeMass},
			// GET_METHOD_1(b2CircleShape, int32, getSupport, GetSupport, const b2Vec2&),
			// GET_METHOD_1(b2CircleShape, const b2Vec2&, getSupportVertex, GetSupportVertex, const b2Vec2&),
			// const b2Vec2& GetVertex(int32 index) const;
			{}
		};

		os->pushGlobals();
		os->pushString("b2CircleShape");
		os->pushUserdata(getClassId<b2CircleShape>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2FixtureDef* toValue<b2FixtureDef*>(OS * os, int offs)
{
	return toObject<b2FixtureDef>(os, offs);
}

template <> const b2FixtureDef* toValue<const b2FixtureDef*>(OS * os, int offs)
{
	return toObject<b2FixtureDef>(os, offs);
}

template <> void pushValue<b2FixtureDef*>(OS * os, b2FixtureDef* val)
{
	pushObject(os, val);
}

template <> int getValueId<b2FixtureDef>(OS * os, b2FixtureDef * val){ return 0; } // (int)val->userData; }
template <> void setValueId<b2FixtureDef>(OS * os, b2FixtureDef * val){} // val->userData = (void*)os->getValueId(); }

struct FixtureDef
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			CONSTRUCT(b2FixtureDef),
			SYNTHESIZE(b2FixtureDef, const b2Shape*, shape),
			{}
		};

		os->pushGlobals();
		os->pushString("b2FixtureDef");
		os->pushUserdata(getClassId<b2FixtureDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

template <> b2Fixture* toValue<b2Fixture*>(OS * os, int offs)
{
	b2Fixture * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Fixture*>(OS * os, b2Fixture* val)
{
	pushObject(os, val);
}

struct Fixture
{
	static int getMassData(OS * os, int params, int, int, void*)
	{
		b2Fixture * fixture = toObject<b2Fixture>(os, -params-1);
		if(fixture){
			b2MassData * data = MassData::pushDefault(os);
			fixture->GetMassData(data);
			// pushValue(os, data); - already in stack
			return 1;
		}
		return 0;
	}

	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD(b2Fixture, b2Shape::Type, type, GetType),
			GET_METHOD(b2Fixture, const b2Shape*, shape, GetShape),
			GET_METHOD(b2Fixture, bool, isSensor, IsSensor),
			SET_METHOD(b2Fixture, bool, isSensor, SetSensor),
			GET_METHOD(b2Fixture, const b2Filter&, filterData, GetFilterData),
			SET_METHOD(b2Fixture, const b2Filter&, filterData, SetFilterData),
			VOID_METHOD(b2Fixture, refilter, Refilter),
			GET_METHOD(b2Fixture, const b2Body*, body, GetBody),
			GET_METHOD(b2Fixture, const b2Fixture*, next, GetNext),
			GET_METHOD_1(b2Fixture, bool, testPoint, TestPoint, const b2Vec2&),
			// bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, int32 childIndex) const;
			{"__get@massData", getMassData},
			GET_METHOD(b2Fixture, float32, density, GetDensity),
			SET_METHOD(b2Fixture, float32, density, SetDensity),
			GET_METHOD(b2Fixture, float32, friction, GetFriction),
			SET_METHOD(b2Fixture, float32, friction, SetFriction),
			GET_METHOD(b2Fixture, float32, restitution, GetRestitution),
			SET_METHOD(b2Fixture, float32, restitution, SetRestitution),
			// const b2AABB& GetAABB(int32 childIndex) const;
			{}
		};

		os->pushGlobals();
		os->pushString("b2Fixture");
		os->pushUserdata(getClassId<b2Fixture>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================
/*
template <> b2Joint* toValue<b2Joint*>(OS * os, int offs)
{
	b2Joint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Joint*>(OS * os, b2Joint* val)
{
	pushObject(os, val);
}
*/
// =====================================================================

template <> b2ManifoldPoint* toValue<b2ManifoldPoint*>(OS * os, int offs)
{
	b2ManifoldPoint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2ManifoldPoint*>(OS * os, b2ManifoldPoint* val)
{
	pushObject(os, val);
}

struct ManifoldPoint
{
	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			SYNTHESIZE_READONLY(b2ManifoldPoint, b2Vec2, localPoint),
			SYNTHESIZE_READONLY(b2ManifoldPoint, float32, normalImpulse),
			SYNTHESIZE_READONLY(b2ManifoldPoint, float32, tangentImpulse),
			{}
		};

		os->pushGlobals();
		os->pushString("b2ManifoldPoint");
		os->pushUserdata(getClassId<b2ManifoldPoint>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2Manifold* toValue<b2Manifold*>(OS * os, int offs)
{
	b2Manifold * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Manifold*>(OS * os, b2Manifold* val)
{
	pushObject(os, val);
}

// =====================================================================

template <> b2Body* toValue<b2Body*>(OS * os, int offs)
{
	b2Body * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Body*>(OS * os, b2Body* val)
{
	pushObject(os, val);
}

template <> b2Shape* toValue<b2Shape*>(OS * os, int offs)
{
	b2Shape * val;
	return toObject(os, val, offs);
}

template <> const b2Shape* toValue<const b2Shape*>(OS * os, int offs)
{
	const b2Shape * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Shape*>(OS * os, b2Shape* val)
{
	pushObject(os, val);
}

struct Body
{
	static int getMassData(OS * os, int params, int, int, void*)
	{
		b2Body * body = (b2Body*)os->toUserdata(getId<b2Body>(), -params-1);
		if(body){
			b2MassData * data = MassData::pushDefault(os);
			body->GetMassData(data);
			// pushValue(os, data); - already in stack
			return 1;
		}
		return 0;
	}

	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_1_NOT_CONST(b2Body, b2Fixture*, createFixture, CreateFixture, const b2FixtureDef*),
			GET_METHOD_2_NOT_CONST(b2Body, b2Fixture*, createFixtureByShape, CreateFixture, const b2Shape*, float32),
			VOID_METHOD_1(b2Body, destroyFixture, DestroyFixture, b2Fixture*),
			VOID_METHOD_2(b2Body, setTransform, SetTransform, const b2Vec2&, float32),
			GET_METHOD(b2Body, const b2Transform&, transform, GetTransform),
			GET_METHOD(b2Body, const b2Vec2&, position, GetPosition),
			GET_METHOD(b2Body, float32, angle, GetAngle),
			GET_METHOD(b2Body, const b2Vec2&, worldCenter, GetWorldCenter),
			GET_METHOD(b2Body, const b2Vec2&, localCenter, GetLocalCenter),
			SET_METHOD(b2Body, const b2Vec2&, linearVelocity, SetLinearVelocity),
			GET_METHOD(b2Body, b2Vec2, linearVelocity, GetLinearVelocity),
			SET_METHOD(b2Body, float32, angularVelocity, SetAngularVelocity),
			GET_METHOD(b2Body, float32, angularVelocity, GetAngularVelocity),
			VOID_METHOD_2(b2Body, applyForce, ApplyForce, const b2Vec2&, const b2Vec2&),
			VOID_METHOD_1(b2Body, applyForceToCenter, ApplyForceToCenter, const b2Vec2&),
			VOID_METHOD_1(b2Body, applyTorque, ApplyTorque, float32),
			VOID_METHOD_2(b2Body, applyLinearImpulse, ApplyLinearImpulse, const b2Vec2&, const b2Vec2&),
			VOID_METHOD_1(b2Body, applyAngularImpulse, ApplyAngularImpulse, float32),
			GET_METHOD(b2Body, float32, mass, GetMass),
			GET_METHOD(b2Body, float32, inertia, GetInertia),
			{"__get@massData", getMassData},
			SET_METHOD(b2Body, const b2MassData*, massData, SetMassData),
			VOID_METHOD(b2Body, resetMassData, ResetMassData),
			GET_METHOD_1(b2Body, b2Vec2, getWorldPoint, GetWorldPoint, const b2Vec2&),
			GET_METHOD_1(b2Body, b2Vec2, getWorldVector, GetWorldVector, const b2Vec2&),
			GET_METHOD_1(b2Body, b2Vec2, getLocalPoint, GetLocalPoint, const b2Vec2&),
			GET_METHOD_1(b2Body, b2Vec2, getLocalVector, GetLocalVector, const b2Vec2&),
			GET_METHOD_1(b2Body, b2Vec2, getLinearVelocityFromWorldPoint, GetLinearVelocityFromWorldPoint, const b2Vec2&),
			GET_METHOD_1(b2Body, b2Vec2, getLinearVelocityFromLocalPoint, GetLinearVelocityFromLocalPoint, const b2Vec2&),
			GET_METHOD_1(b2Body, b2Vec2, getLocalPoint, GetLocalPoint, const b2Vec2&),
			GET_METHOD(b2Body, float32, linearDamping, GetLinearDamping),
			SET_METHOD(b2Body, float32, linearDamping, SetLinearDamping),
			GET_METHOD(b2Body, float32, angularDamping, GetAngularDamping),
			SET_METHOD(b2Body, float32, angularDamping, SetAngularDamping),
			GET_METHOD(b2Body, float32, gravityScale, GetGravityScale),
			SET_METHOD(b2Body, float32, gravityScale, SetGravityScale),
			GET_METHOD(b2Body, b2BodyType, type, GetType),
			SET_METHOD(b2Body, b2BodyType, type, SetType),
			SET_METHOD(b2Body, bool, isBullet, SetBullet),
			GET_METHOD(b2Body, bool, isBullet, IsBullet),
			SET_METHOD(b2Body, bool, isSleepingAllowed, SetSleepingAllowed),
			GET_METHOD(b2Body, bool, isSleepingAllowed, IsSleepingAllowed),
			SET_METHOD(b2Body, bool, isAwake, SetAwake),
			GET_METHOD(b2Body, bool, isAwake, IsAwake),
			SET_METHOD(b2Body, bool, isActive, SetActive),
			GET_METHOD(b2Body, bool, isActive, IsActive),
			SET_METHOD(b2Body, bool, isFixedRotation, SetFixedRotation),
			GET_METHOD(b2Body, bool, isFixedRotation, IsFixedRotation),
			GET_METHOD(b2Body, const b2Fixture*, fixtureList, GetFixtureList),
			GET_METHOD(b2Body, const b2JointEdge*, jointList, GetJointList),
			GET_METHOD(b2Body, const b2ContactEdge*, contactList, GetContactList),
			GET_METHOD(b2Body, const b2Body*, next, GetNext),
			GET_METHOD(b2Body, const b2World*, world, GetWorld),
			{}
		};

		os->pushGlobals();
		os->pushString("b2Body");
		os->pushUserdata(getClassId<b2Body>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

} // Box2dObjectScript

using namespace Box2dObjectScriptOld;

void initBox2dOld(OS * os)
{
	World::init(os);
	BodyDef::init(os);
	Body::init(os);
	JointEdge::init(os);
	ContactEdge::init(os);
	Contact::init(os);
	WheelJointDef::init(os);
	WheelJoint::init(os);
	WeldJointDef::init(os);
	WeldJoint::init(os);
	RopeJointDef::init(os);
	RopeJoint::init(os);
	RevoluteJointDef::init(os);
	RevoluteJoint::init(os);
	PulleyJointDef::init(os);
	PulleyJoint::init(os);
	PrismaticJointDef::init(os);
	PrismaticJoint::init(os);
	MouseJointDef::init(os);
	MouseJoint::init(os);
	GearJointDef::init(os);
	GearJoint::init(os);
	FrictionJointDef::init(os);
	FrictionJoint::init(os);
	DistanceJointDef::init(os);
	DistanceJoint::init(os);
	MassData::init(os);
	CircleShape::init(os);
	FixtureDef::init(os);
	Fixture::init(os);
	ManifoldPoint::init(os);
	Fixture::init(os);
}
#endif