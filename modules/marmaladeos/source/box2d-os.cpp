#include "box2d-os.h"
#include "Box2D\Box2D.h"

using namespace ObjectScript;

namespace Box2dObjectScript {

// =====================================================================

static float32 physicsMetricScale = 100.0f;

static float32 toBox2dMetric(float32 x)
{
	return x / physicsMetricScale;
}

static float32 fromBox2dMetric(float32 x)
{
	return x * physicsMetricScale;
}

// =====================================================================

template <class T> struct RemoveConst          { typedef T type; };
template <class T> struct RemoveConst<const T> { typedef T type; };
template <class T> struct RemoveConst<const T&> { typedef T type; };

template <class T> struct RemoveRef		{ typedef T type; };
template <class T> struct RemoveRef<T&> { typedef T type; };

template <class T> struct RemovePtr		{ typedef T type; };
template <class T> struct RemovePtr<T*> { typedef T type; };

template <class T> struct PlainType { typedef typename RemovePtr<typename RemoveRef<typename RemoveConst<T>::type>::type>::type type; };

// =====================================================================

template <class T> int getClassId(){ static int id = (int)&id; return id; }
template <class T> int getId(){ static int id = (int)&id; return id; }

// =====================================================================

template <class T> const char * getClassName();

template <> const char * getClassName<float32>(){ return "float32"; }
template <> const char * getClassName<int>(){ return "int"; }
template <> const char * getClassName<bool>(){ return "bool"; }
template <> const char * getClassName<b2Vec2>(){ return "b2Vec2"; }
template <> const char * getClassName<b2Transform>(){ return "b2Transform"; }

// template <> const char * getClassName<b2Shape>(){ return "b2Shape"; }
template <> const char * getClassName<b2CircleShape>(){ return "b2CircleShape"; }
template <> const char * getClassName<b2EdgeShape>(){ return "b2EdgeShape"; }
template <> const char * getClassName<b2LoopShape>(){ return "b2LoopShape"; }
template <> const char * getClassName<b2PolygonShape>(){ return "b2PolygonShape"; }

template <> const char * getClassName<b2RopeJoint>(){ return "b2RopeJoint"; }
template <> const char * getClassName<b2RevoluteJoint>(){ return "b2RevoluteJoint"; }
template <> const char * getClassName<b2PulleyJoint>(){ return "b2PulleyJoint"; }
template <> const char * getClassName<b2PrismaticJoint>(){ return "b2PrismaticJoint"; }
template <> const char * getClassName<b2MouseJoint>(){ return "b2MouseJoint"; }
template <> const char * getClassName<b2GearJoint>(){ return "b2GearJoint"; }
template <> const char * getClassName<b2FrictionJoint>(){ return "b2FrictionJoint"; }
template <> const char * getClassName<b2DistanceJoint>(){ return "b2DistanceJoint"; }
template <> const char * getClassName<b2WheelJoint>(){ return "b2WheelJoint"; }
template <> const char * getClassName<b2WeldJoint>(){ return "b2WeldJoint"; }

// template <> const char * getClassName<b2ManifoldPoint>(){ return "b2ManifoldPoint"; }

template <> const char * getClassName<b2Fixture>(){ return "b2Fixture"; }
template <> const char * getClassName<b2Contact>(){ return "b2Contact"; }
template <> const char * getClassName<b2ContactImpulse>(){ return "b2ContactImpulse"; }
template <> const char * getClassName<b2Body>(){ return "b2Body"; }
template <> const char * getClassName<b2BodyType>(){ return "b2BodyType"; }
// template <> const char * getClassName<b2JointEdge>(){ return "b2JointEdge"; }
// template <> const char * getClassName<b2ContactEdge>(){ return "b2ContactEdge"; }
// template <> const char * getClassName<b2MassData>(){ return "b2MassData"; }
template <> const char * getClassName<b2Manifold>(){ return "b2Manifold"; }

template <> const char * getClassName<class World>(){ return "b2World"; }

// =====================================================================

template <class T> void osObjectDestructor(OS * os, void * data, void * user_param)
{
}

template <> void osObjectDestructor<b2Body>(OS * os, void * data, void * user_param)
{
#if 1
	b2Body * body = (b2Body*)data;
	if(body){
		body->GetWorld()->DestroyBody(body);
	}
#endif
}

void osJointDestructor(OS * os, void * data, void * user_param)
{
#if 1
	b2Joint * joint = (b2Joint*)data;
	if(joint){
		b2Body * body = joint->GetBodyA();
		if(body || (body = joint->GetBodyB())){
			body->GetWorld()->DestroyJoint(joint);
		}else{
			OS_ASSERT(false);
		}
	}
#endif
}

template <> void osObjectDestructor<b2Joint>(OS * os, void * data, void * user_param)
{
	osJointDestructor(os, data, user_param);
}

// =====================================================================

template <class T>
struct Box2dValue
{
};

// =====================================================================

template <class T>
struct Box2dValue<T*>
{
	typedef typename RemoveConst<T>::type * type;

	static bool isValid(type obj){ return obj != NULL; }

	static type to(typename RemoveConst<T>::type * val){ return (type)val; }
	static type to(const typename RemoveConst<T>::type * val){ return (type)val; }

	static type to(OS * os, int offs)
	{
		return (type)os->toUserdata(getId<T>(), offs);
	}

	static int getValueId(OS * os, type val)
	{
		return (int)val->GetUserData();
	}

	static void setValueId(OS * os, type val)
	{
		val->SetUserData((void*)os->getValueId());
	}

	static void push(OS * os, type val)
	{
		if(!val){
			os->pushNull();
			return;
		}
		int valueId = getValueId(os, val);
		if(valueId){
			os->pushValueById(valueId);
			if(!os->isNull()){
				OS_ASSERT(os->isUserdata(getId<T>(), -1));
				return;
			}
			os->pop();
		}
		os->pushUserPointer(getId<T>(), val, osObjectDestructor<T>);
		setValueId(os, val);
		os->pushStackValue();
		os->getGlobal(getClassName<T>());
		OS_ASSERT(os->isUserdata(getClassId<T>(), -1));
		os->setPrototype(getId<T>());
	}
};

template <class T> struct Box2dValue<const T*>: public Box2dValue<T*> {};
template <class T> struct Box2dValue<const T&>: public Box2dValue<T> {};

// =====================================================================

template <>
struct Box2dValue<float32>
{
	typedef float32 type;

	static bool isValid(float32){ return true; }

	static type to(float32 val){ return (type)val; }
	static float32 to(OS * os, int offs)
	{
		return os->toFloat(offs);
	}

	static void push(OS * os, float32 val)
	{
		os->pushNumber(val);
	}
};

template <>
struct Box2dValue<int32>
{
	typedef int32 type;

	static bool isValid(int32){ return true; }

	static type to(int32 val){ return (type)val; }
	static int32 to(OS * os, int offs)
	{
		return os->toInt(offs);
	}

	static void push(OS * os, int32 val)
	{
		os->pushNumber(val);
	}
};

template <>
struct Box2dValue<bool>
{
	typedef bool type;

	static bool isValid(bool){ return true; }

	static type to(bool val){ return (type)val; }
	static bool to(OS * os, int offs)
	{
		return os->toBool(offs);
	}

	static void push(OS * os, bool val)
	{
		os->pushBool(val);
	}
};

// =====================================================================

template <>
struct Box2dValue<b2BodyType>
{
	typedef b2BodyType type;

	static bool isValid(b2BodyType){ return true; }

	static type to(b2BodyType val){ return (type)val; }
	static b2BodyType to(OS * os, int offs)
	{
		OS::String str = os->toString(offs);
		if(str == "static") return b2_staticBody;
		if(str == "kinematic") return b2_kinematicBody;
		// if(str == "dynamic") return b2_dynamicBody;
		return b2_dynamicBody;
	}

	static void push(OS * os, b2BodyType val)
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
};

// =====================================================================

template <>
struct Box2dValue<b2JointType>
{
	typedef b2JointType type;

	static bool isValid(b2JointType){ return true; }

	static type to(b2JointType val){ return (type)val; }
	static b2JointType to(OS * os, int offs)
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

	static void push(OS * os, b2JointType val)
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
};

// =====================================================================

template <>
struct Box2dValue<b2Vec2>
{
	typedef b2Vec2 type;

	static bool isValid(const b2Vec2&){ return true; }

	static type to(const b2Vec2& val){ return (type)val; }
	static b2Vec2 to(OS * os, int offs)
	{
		if(os->isObject(offs)){
			os->getProperty(offs, "x"); // required
			float x = toBox2dMetric(os->popNumber());
		
			os->getProperty(offs, "y"); // required
			float y = toBox2dMetric(os->popNumber());

			return b2Vec2(x, y);
		}else if(os->isArray(offs)){
			os->pushStackValue(offs);
			os->pushNumber(0);
			os->getProperty();
			float x = toBox2dMetric(os->popNumber());
		
			os->pushStackValue(offs);
			os->pushNumber(1);
			os->getProperty();
			float y = toBox2dMetric(os->popNumber());

			return b2Vec2(x, y);
		}
		os->triggerError(OS_E_ERROR, "point expected");
		return b2Vec2(0, 0);
	}

	static void push(OS * os, const b2Vec2& p)
	{
		os->newObject();
	
		os->pushStackValue();
		os->pushNumber(fromBox2dMetric(p.x));
		os->setProperty("x", false, false);
				
		os->pushStackValue();
		os->pushNumber(fromBox2dMetric(p.y));
		os->setProperty("y", false, false);
	}
};

// =====================================================================

template <>
struct Box2dValue<b2Color>
{
	typedef b2Color type;

	static bool isValid(const b2Color&){ return true; }

	static type to(const b2Color& val){ return (type)val; }
	static b2Color to(OS * os, int offs)
	{
		if(os->isObject(offs)){
			os->getProperty(offs, "r"); // required
			float r = os->popFloat(1.0f);
		
			os->getProperty(offs, "g"); // required
			float g = os->popFloat(1.0f);

			os->getProperty(offs, "b"); // required
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
		os->triggerError(OS_E_ERROR, "color expected");
		return b2Color(1, 1, 1);
	}

	static void push(OS * os, const b2Color& color)
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
};

// =====================================================================

template <>
struct Box2dValue<b2Transform>
{
	typedef b2Transform type;

	static bool isValid(const b2Transform&){ return true; }

	static type to(const b2Transform& val){ return (type)val; }
	static b2Transform to(OS * os, int offs)
	{
		if(os->isObject(offs)){
			os->getProperty(offs, "x"); // required
			float x = toBox2dMetric(os->popFloat());
		
			os->getProperty(offs, "y"); // required
			float y = toBox2dMetric(os->popFloat());
		
			os->getProperty(offs, "angle"); // required
			float angle = os->popFloat();

			return b2Transform(b2Vec2(x, y), b2Rot(angle));
		}
		os->triggerError(OS_E_ERROR, "b2Transform expected");
		return b2Transform(b2Vec2(0, 0), b2Rot(0));
	}

	static void push(OS * os, const b2Transform& xf)
	{
		os->newObject();
	
		os->pushStackValue();
		os->pushNumber(fromBox2dMetric(xf.p.x));
		os->setProperty("x", false, false);
				
		os->pushStackValue();
		os->pushNumber(fromBox2dMetric(xf.p.y));
		os->setProperty("y", false, false);
				
		os->pushStackValue();
		os->pushNumber(xf.q.GetAngle());
		os->setProperty("angle", false, false);
	}
};

// =====================================================================

template <>
struct Box2dValue<b2Profile>
{
	typedef b2Profile type;

	static bool isValid(const b2Profile&){ return true; }

	static type to(const b2Profile& val){ return (type)val; }

	static void push(OS * os, const b2Profile& p)
	{
		os->newObject();
		OS::NumberDef numbers[] = {
			{"step", p.step},
			{"collide", p.collide},
			{"solve", p.solve},
			{"solveInit", p.solveInit},
			{"solveVelocity", p.solveVelocity},
			{"solvePosition", p.solvePosition},
			{"broadphase", p.broadphase},
			{"solveTOI", p.solveTOI},
			{}
		};
		os->setNumbers(numbers, false);
	}
};

// =====================================================================

template <class T>
struct Box2dSimpleObject
{
};

template <class T>
struct Box2dSimpleObject<T*>
{
	typedef T * type;

	static bool isValid(type obj){ return obj != NULL; }

	static type to(T * val){ return (type)val; }
	static type to(const T * val){ return (type)val; }

	static type to(OS * os, int offs)
	{
		return (type)os->toUserdata(getId<T>(), offs);
	}

	static void push(OS * os, type val)
	{
		if(!val){
			os->pushNull();
			return;
		}
		os->pushUserPointer(getId<T>(), val, osObjectDestructor<T>);
		os->pushStackValue();
		os->getGlobal(getClassName<T>());
		OS_ASSERT(os->isUserdata(getClassId<T>(), -1));
		os->setPrototype(getId<T>());
	}
};

// =====================================================================

template <> struct Box2dValue<b2Contact*>: public Box2dSimpleObject<b2Contact*> {};

// =====================================================================

template <> struct Box2dValue<b2Manifold*>: public Box2dSimpleObject<b2Manifold*> {};
template <> struct Box2dValue<const b2Manifold*>: public Box2dSimpleObject<b2Manifold*> {};

// =====================================================================

template <> struct Box2dValue<b2ContactImpulse*>: public Box2dSimpleObject<b2ContactImpulse*> {};
template <> struct Box2dValue<const b2ContactImpulse*>: public Box2dSimpleObject<b2ContactImpulse*> {};

// =====================================================================

template <class T> T * toBox2dObject(OS * os, int offs)
{
	return Box2dValue<T*>::to(os, offs);
}

template <class T> void pushBox2dValue(OS * os, T obj)
{
	Box2dValue< typename RemoveConst<T>::type >::push(os, 
		Box2dValue< typename RemoveConst<T>::type >::to(obj));
}

// =====================================================================

void pushXY(OS * os, const b2Vec2& p)
{
	os->pushNumber(fromBox2dMetric(p.x));
	os->pushNumber(fromBox2dMetric(p.y));
}

void pushVertices(OS * os, const b2Vec2* vertices, int count)
{
	os->newArray(count);
	for(int i = 0; i < count; i++){
		os->pushStackValue();
		pushBox2dValue(os, vertices[i]);
		os->addProperty();
	}
}

// =====================================================================

template <class T> void clearUserdata(OS * os, T * val)
{
	os->pushValueById((int)val->GetUserData());
	os->clearUserdata(getId<T>());
	os->pop();
}

// =====================================================================

#define GET_SELF(argType) \
	argType * self = toBox2dObject<argType>(os, -params-1); \
	if(!self){ \
		os->triggerError(OS_E_ERROR, OS::String(os, getClassName<argType>())+" this is wrong"); \
		return 0; \
	}

#define GET_TEMPLATE_ARG(num, argType) \
	typename Box2dValue<argType>::type arg##num = Box2dValue<argType>::to(os, -params+num-1); \
	if(!Box2dValue<argType>::isValid(arg##num)){ \
		os->triggerError(OS_E_ERROR, OS::String(os, getClassName< PlainType<argType>::type >())+" expected"); \
		return 0; \
	}

#define GET_ARG(num, argType) \
	Box2dValue<argType>::type arg##num = Box2dValue<argType>::to(os, -params+num-1); \
	if(!Box2dValue<argType>::isValid(arg##num)){ \
		os->triggerError(OS_E_ERROR, OS::String(os, getClassName< PlainType<argType>::type >())+" expected"); \
		return 0; \
	}

// =====================================================================

template <class T, class resType, class T2, resType(T2::*method)()const> 
int getFieldByMethod(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	Box2dValue<typename RemoveConst<resType>::type>::push(os, Box2dValue<typename RemoveConst<resType>::type>::to((self->*method)()));
	return 1;
}

template <class T, class resType, class T2, resType(T2::*method)()> 
int getFieldByMethodNotConst(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	typedef typename RemoveConst<resType>::type type;
	Box2dValue<type>::push(os, Box2dValue<type>::to((self->*method)()));
	return 1;
}

// =====================================================================

template <class T, class resType, class argType1, class T2, resType(T2::*method)(argType1)const> 
int getFieldByMethodArg1(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	GET_TEMPLATE_ARG(1, argType1);
	typedef typename RemoveConst<resType>::type type;
	Box2dValue<type>::push(os, Box2dValue<type>::to((self->*method)(arg1)));
	return 1;
}

template <class T, class resType, class argType1, class T2, resType(T2::*method)(argType1)> 
int getFieldByMethodArg1NotConst(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	GET_TEMPLATE_ARG(1, argType1);
	typedef typename RemoveConst<resType>::type type;
	Box2dValue<resType>::push(os, Box2dValue<resType>::to((self->*method)(arg1)));
	return 1;
}

// =====================================================================

template <class T, class resType, class argType1, class argType2, class T2, resType(T2::*method)(argType1, argType2)> 
int getFieldByMethodArgs2NotConst(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	GET_TEMPLATE_ARG(1, argType1);
	GET_TEMPLATE_ARG(2, argType2);
	typedef typename RemoveConst<resType>::type type;
	Box2dValue<type>::push(os, Box2dValue<type>::to((self->*method)(arg1, arg2)));
	return 1;
}

// =====================================================================

template <class T, class T2, void(T2::*method)()> 
int voidMethod(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	(self->*method)();
	return 0;
}

template <class T, class argType1, class T2, void(T2::*method)(argType1)> 
int voidMethodArg1(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	GET_TEMPLATE_ARG(1, argType1);
	(self->*method)(arg1);
	return 0;
}

template <class T, class argType1, class argType2, class T2, void(T2::*method)(argType1, argType2)> 
int voidMethodArgs2(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	GET_TEMPLATE_ARG(1, argType1);
	GET_TEMPLATE_ARG(2, argType2);
	(self->*method)(arg1, arg2);
	return 0;
}

template <class T, class argType1, class argType2, class argType3, class T2, void(T2::*method)(argType1, argType2, argType3)> 
int voidMethodArgs3(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	GET_TEMPLATE_ARG(1, argType1);
	GET_TEMPLATE_ARG(2, argType2);
	GET_TEMPLATE_ARG(3, argType3);
	(self->*method)(arg1, arg2, arg3);
	return 0;
}

template <class T, class argType1, class argType2, class argType3, class argType4, class argType5, class argType6, class argType7,
	class T2, void(T2::*method)(argType1, argType2, argType3, argType4, argType5, argType6, argType7)> 
int voidMethodArgs7(OS * os, int params, int, int, void*)
{
	GET_SELF(T);
	GET_TEMPLATE_ARG(1, argType1);
	GET_TEMPLATE_ARG(2, argType2);
	GET_TEMPLATE_ARG(3, argType3);
	GET_TEMPLATE_ARG(4, argType4);
	GET_TEMPLATE_ARG(5, argType5);
	GET_TEMPLATE_ARG(6, argType6);
	GET_TEMPLATE_ARG(7, argType7);
	(self->*method)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	return 0;
}

// =====================================================================

#define GET_METHOD(T, resType, name, method)  {"__get@"#name, getFieldByMethod<T, resType, T, & T::method>}
#define GET_METHOD_NOT_CONST(T, resType, name, method)  {"__get@"#name, getFieldByMethodNotConst<T, resType, T, & T::method>}
#define GET_METHOD_SPEC(T, resType, name, T2, method)  {"__get@"#name, getFieldByMethod<T, resType, T2, & T2::method>}

#define GET_METHOD_1(T, resType, name, method, argType1)  {"__get@"#name, getFieldByMethodArg1<T, resType, argType1, T, & T::method>}
#define GET_METHOD_1_NOT_CONST(T, resType, name, method, argType1)  {"__get@"#name, getFieldByMethodArg1NotConst<T, resType, argType1, T, & T::method>}
#define GET_METHOD_2_NOT_CONST(T, resType, name, method, argType1, argType2)  {"__get@"#name, getFieldByMethodArgs2NotConst<T, resType, argType1, argType2, T, & T::method>}

#define SET_METHOD(T, resType, name, method)  {"__set@"#name, voidMethodArg1<T, resType, T, & T::method>}
#define SET_METHOD_SPEC(T, resType, name, T2, method)  {"__set@"#name, voidMethodArg1<T, resType, T2, & T2::method>}

#define VOID_METHOD(T, name, method)  {#name, voidMethod<T, T, & T::method>}
#define VOID_METHOD_1(T, name, method, argType1)  {#name, voidMethodArg1<T, argType1, T, & T::method>}
#define VOID_METHOD_2(T, name, method, argType1, argType2)  {#name, voidMethodArgs2<T, argType1, argType2, T, & T::method>}
#define VOID_METHOD_3(T, name, method, argType1, argType2, argType3)  {#name, voidMethodArgs3<T, argType1, argType2, argType3, T, & T::method>}
#define VOID_METHOD_7(T, name, method, argType1, argType2, argType3, argType4, argType5, argType6, argType7)  {#name, voidMethodArgs7<T, argType1, argType2, argType3, argType4, argType5, argType6, argType7, T, & T::method>}

#define VOID_METHOD_SPEC(T, name, T2, method)  {#name, voidMethod<T, T2, & T2::method>}
#define VOID_METHOD_1_SPEC(T, name, T2, method, argType1)  {#name, voidMethodArg1<T, argType1, T2, & T2::method>}
#define VOID_METHOD_2_SPEC(T, name, T2, method, argType1, argType2)  {#name, voidMethodArgs2<T, argType1, argType2, T2, & T2::method>}
#define VOID_METHOD_3_SPEC(T, name, T2, method, argType1, argType2, argType3)  {#name, voidMethodArgs3<T, argType1, argType2, argType3, T2, & T2::method>}
#define VOID_METHOD_7_SPEC(T, name, T2, method, argType1, argType2, argType3, argType4, argType5, argType6, argType7)  {#name, voidMethodArgs7<T, argType1, argType2, argType3, argType4, argType5, argType6, argType7, T2, & T2::method>}

// =====================================================================

template <class T>
void initClass(OS * os, OS::FuncDef * list)
{
	os->pushGlobals();
	os->pushString(getClassName<T>());
	os->pushUserdata(getClassId<T>(), 0);
	os->setFuncs(list);
	os->setProperty();
}

template <class T> T * error(T * obj, OS * os, const char * message, int pop = 1)
{
	if(obj){
		obj->~T();
		os->free(obj);
	}
	os->triggerError(OS_E_ERROR, message);
	os->pop(pop);
	return NULL;
}

int error(OS * os, const char * message, int pop = 1)
{
	os->triggerError(OS_E_ERROR, message);
	os->pop(pop);
	return 0;
}

// =====================================================================

class World: public b2World, b2DestructionListener, b2ContactFilter, b2ContactListener, b2Draw, b2QueryCallback, b2RayCastCallback
{
public:

	OS * os;
	int osId; // weak ref to ObjectScript value
	// float metricScale;

	static World * toWorld(b2World * w)
	{
		return (World*)((char*)w - (int)(b2World*)((World*)NULL));
	}

	World(OS * p_os, const b2Vec2& gravity, bool doSleep): b2World(gravity, doSleep)
	{
		os = p_os;
		osId = os->getValueId();
		// metricScale = p_metricScale;
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
		os->getProperty(name, false, false); // getters disabled
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
		// clearUserdata(os, joint);
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
			pushBox2dValue(os, fixtureA);
			pushBox2dValue(os, fixtureB);
			os->call(2, 1);
			return os->popBool();
		}
		return true;
	}

	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact)
	{ 
		if(getFunction("beginContact")){
			pushBox2dValue(os, contact);
			os->call(1, 0);
		}
	}

	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact)
	{ 
		if(getFunction("endContact")){
			pushBox2dValue(os, contact);
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
			pushBox2dValue(os, contact);
			pushBox2dValue(os, oldManifold);
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
			pushBox2dValue(os, contact);
			pushBox2dValue(os, impulse);
			os->call(2, 0);
		}
	}

	/// Draw a closed polygon provided in CCW order.
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if(getFunction("drawPolygon")){
			pushVertices(os, vertices, vertexCount);
			pushBox2dValue(os, color);
			pushBox2dValue(os, false);
			os->call(3, 0);
		}
	}

	/// Draw a solid closed polygon provided in CCW order.
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if(getFunction("drawPolygon")){
			pushVertices(os, vertices, vertexCount);
			pushBox2dValue(os, color);
			pushBox2dValue(os, true);
			os->call(3, 0);
		}
	}

	/// Draw a circle.
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		if(getFunction("drawCircle")){
			pushXY(os, center);
			pushBox2dValue(os, radius);
			pushBox2dValue(os, color);
			pushBox2dValue(os, false);
			os->call(5, 0);
		}
	}
	
	/// Draw a solid circle.
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		if(getFunction("drawSolidCircle")){
			pushXY(os, center);
			pushBox2dValue(os, radius);
			pushBox2dValue(os, color);
			pushBox2dValue(os, true);
			os->call(5, 0);
		}
	}
	
	/// Draw a line segment.
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		if(getFunction("drawSegment")){
			pushXY(os, p1);
			pushXY(os, p2);
			pushBox2dValue(os, color);
			os->call(5, 0);
		}
	}

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	void DrawTransform(const b2Transform& xf)
	{
		if(getFunction("drawTransform")){
			pushBox2dValue(os, xf);
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
		pushBox2dValue(os, fixture);
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
		pushBox2dValue(os, fixture);
		pushXY(os, point);
		pushXY(os, normal);
		pushBox2dValue(os, fraction);
		os->call(6, 1);
		return os->popFloat(1.0f);
	}

	static void createBodyFixture(b2Body*, OS*, int offs);

	static int createBody(OS * os, int params, int, int, void*)
	{
		GET_SELF(World);
		if(!os->isObject(-params)) return error(os, "body def object expected");

		b2BodyDef def;
		int offs = os->getAbsoluteOffs(-params);

		os->getProperty(offs, "type", false); // optional because of we handle error next line of code
		if(os->isNull()) return error(os, "type expected by body def");
		def.type = Box2dValue<b2BodyType>::to(os, -1);
		os->pop();

		os->getProperty(offs, "position", false); // optional
		if(os->isNull()){
			os->pop();

			os->getProperty(offs, "x", false); // optional
			def.position.x = toBox2dMetric(os->popFloat(fromBox2dMetric(def.position.x)));
			
			os->getProperty(offs, "y", false); // optional
			def.position.y = toBox2dMetric(os->popFloat(fromBox2dMetric(def.position.y)));
		}else{
			def.position = Box2dValue<b2Vec2>::to(os, -1);
			os->pop();
		}
		// def.position.x *= self->metricScale;
		// def.position.y *= self->metricScale;

		os->getProperty(offs, "angle", false); // optional
		def.angle = os->popFloat(def.angle);

		os->getProperty(offs, "linearVelocity", false); // optional
		def.linearVelocity = os->isNull() ? def.linearVelocity : Box2dValue<b2Vec2>::to(os, -1);
		os->pop();

		os->getProperty(offs, "angularVelocity", false); // optional
		def.angularVelocity = os->popFloat(def.angularVelocity);

		os->getProperty(offs, "linearDamping", false); // optional
		def.linearDamping = os->popFloat(def.linearDamping);

		os->getProperty(offs, "angularDamping", false); // optional
		def.angularDamping = os->popFloat(def.angularDamping);

		os->getProperty(offs, "allowSleep", false); // optional
		def.allowSleep = os->popBool(def.allowSleep);

		os->getProperty(offs, "awake", false); // optional
		def.awake = os->popBool(def.awake);

		os->getProperty(offs, "fixedRotation", false); // optional
		def.fixedRotation = os->popBool(def.fixedRotation);

		os->getProperty(offs, "bullet", false); // optional
		def.bullet = os->popBool(def.bullet);

		os->getProperty(offs, "active", false); // optional
		def.active = os->popBool(def.active);

		os->getProperty(offs, "gravityScale", false); // optional
		def.gravityScale = os->popFloat(def.gravityScale);

		b2Body * body = self->CreateBody(&def);
		pushBox2dValue(os, body);

		os->getProperty(offs, "fixture", false); // optional
		if(os->isObject()){
			createBodyFixture(body, os, -1);
		}
		os->pop();

		os->getProperty(offs, "fixtures", false); // optional
		if(os->isArray()){
			int count = os->getLen();
			for(int i = 0; i < count; i++){
				os->pushStackValue();
				os->pushNumber(i);
				os->getProperty();
				if(os->isObject()){
					createBodyFixture(body, os, -1);
					os->pop();
				}
			}
		}
		os->pop();

		return 1;
	}

	static int destroyBody(OS * os, int params, int, int, void*)
	{
		GET_SELF(World);
		GET_ARG(1, b2Body*);
		clearUserdata(os, arg1);
		self->DestroyBody(arg1);
		return 0;
	}

	int createRevoluteJoint(OS * os, int offs)
	{
		return 0;
	}

	int createPrismaticJoint(OS * os, int offs)
	{
		return 0;
	}

	int createDistanceJoint(OS * os, int offs)
	{
		return 0;
	}

	int createPulleyJoint(OS * os, int offs)
	{
		return 0;
	}

	int createMouseJoint(OS * os, int offs)
	{
		return 0;
	}

	int createGearJoint(OS * os, int offs)
	{
		return 0;
	}

	int createWheelJoint(OS * os, int offs)
	{
		return 0;
	}

	int createWeldJoint(OS * os, int offs)
	{
		return 0;
	}

	int createFrictionJoint(OS * os, int offs)
	{
		return 0;
	}

	int createRopeJoint(OS * os, int offs)
	{
		return 0;
	}

	static int createJoint(OS * os, int params, int, int, void*)
	{
		GET_SELF(World);
		if(!os->isObject(-params)) return error(os, "joint def object expected");
		int offs = os->getAbsoluteOffs(-params);

		os->getProperty(offs, "type", false); // optional because of we handle error next line of code
		if(os->isNull()) return error(os, "type expected by joint def");
		b2JointType type = Box2dValue<b2JointType>::to(os, -1); os->pop();
		switch(type){
		case e_revoluteJoint:	return self->createRevoluteJoint(os, offs);
		case e_prismaticJoint:	return self->createPrismaticJoint(os, offs);
		case e_distanceJoint:	return self->createDistanceJoint(os, offs);
		case e_pulleyJoint:		return self->createPulleyJoint(os, offs);
		case e_mouseJoint:		return self->createMouseJoint(os, offs);
		case e_gearJoint:		return self->createGearJoint(os, offs);
		case e_wheelJoint:		return self->createWheelJoint(os, offs);
		case e_weldJoint:		return self->createWeldJoint(os, offs);
		case e_frictionJoint:	return self->createFrictionJoint(os, offs);
		case e_ropeJoint:		return self->createRopeJoint(os, offs);
		}
		return error(os, "error joint type");
	}

	static int destroyJoint(OS * os, int params, int, int, void*)
	{
#if 0
		GET_SELF(World);
		GET_ARG(1, b2Joint*);
		clearUserdata(os, arg1);
		self->DestroyJoint(arg1);
#endif
		return 0;
	}

	static void destructor(OS * os, void * data, void * user_param)
	{
		World * world = (World*)data;
		world->~World();
	}

	static int create(OS * os, int params, int, int, void*)
	{
		b2Vec2 gravity = params > 0 ? Box2dValue<b2Vec2>::to(os, -params) : b2Vec2(0, 9.8f);
		bool sleep = os->toBool(-params+1, true);
		new (os->pushUserdata(getId<World>(), sizeof(World), destructor)) World(os, gravity, sleep);
		os->retainValueById(os->getValueId());
		os->pushStackValue();
		os->getGlobal(getClassName<World>());
		OS_ASSERT(os->isUserdata(getClassId<World>(), -1));
		os->setPrototype(getId<World>());
		return 1;
	}

	static int getMetricScale(OS * os, int params, int, int, void*)
	{
		os->pushNumber(physicsMetricScale);
		return 1;
	}

	static int setMetricScale(OS * os, int params, int, int, void*)
	{
		physicsMetricScale = os->toFloat(-params, 100.0f);
		return 0;
	}

	static void init(OS * os)
	{
		OS::FuncDef funcs[] = {
			{"__construct", create},
			{"__get@metricScale", getMetricScale},
			{"__set@metricScale", setMetricScale},
			{"createBody", createBody},
			{"destroyBody", destroyBody},
			{"createJoint", createJoint},
			{"destroyJoint", destroyJoint},
			VOID_METHOD_3_SPEC(World, step, b2World, Step, float32, int32, int32),
			VOID_METHOD_SPEC(World, clearForces, b2World, ClearForces),
			VOID_METHOD_SPEC(World, drawDebugData, b2World, DrawDebugData),
			// void QueryAABB(b2QueryCallback* callback, const b2AABB& aabb) const;
			// void RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2) const;
			GET_METHOD_SPEC(World, const b2Body*, bodyList, b2World, GetBodyList),
			// GET_METHOD_SPEC(World, const b2Joint*, jointList, b2World, GetJointList),
			GET_METHOD_SPEC(World, const b2Contact*, contactList, b2World, GetContactList),
			SET_METHOD_SPEC(World, bool, warmStarting, b2World, SetWarmStarting),
			SET_METHOD_SPEC(World, bool, continuousPhysics, b2World, SetContinuousPhysics),
			SET_METHOD_SPEC(World, bool, subStepping, b2World, SetSubStepping),
			GET_METHOD_SPEC(World, int32, proxyCount, b2World, GetProxyCount),
			GET_METHOD_SPEC(World, int32, bodyCount, b2World, GetBodyCount),
			GET_METHOD_SPEC(World, int32, jointCount, b2World, GetJointCount),
			GET_METHOD_SPEC(World, int32, contactCount, b2World, GetContactCount),
			GET_METHOD_SPEC(World, int32, treeHeight, b2World, GetTreeHeight),
			GET_METHOD_SPEC(World, int32, treeBalance, b2World, GetTreeBalance),
			GET_METHOD_SPEC(World, float32, treeQuality, b2World, GetTreeQuality),
			GET_METHOD_SPEC(World, b2Vec2, gravity, b2World, GetGravity),
			SET_METHOD_SPEC(World, const b2Vec2&, gravity, b2World, SetGravity),
			GET_METHOD_SPEC(World, bool, isLocked, b2World, IsLocked),
			GET_METHOD_SPEC(World, bool, autoClearForces, b2World, GetAutoClearForces),
			SET_METHOD_SPEC(World, bool, autoClearForces, b2World, SetAutoClearForces),
			GET_METHOD_SPEC(World, const b2Profile&, profile, b2World, GetProfile),
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

		// initClass<World>(os, funcs);
		os->pushGlobals();
		os->pushString(getClassName<World>());
		os->pushUserdata(getClassId<World>(), 0);
		os->setFuncs(funcs);
		os->setNulls(nulls);
		os->setProperty();
	}
};

template <>
struct Box2dValue<World*>
{
	typedef World * type;

	static bool isValid(type obj){ return obj != NULL; }

	static type to(World * val){ return (type)val; }
	static type to(const World * val){ return (type)val; }

	static type to(OS * os, int offs)
	{
		return (type)os->toUserdata(getId<World>(), offs);
	}

	static void push(OS * os, type val)
	{
		if(!val){
			os->pushNull();
			return;
		}
		os->pushValueById(val->osId);
		if(!os->isNull()){
			OS_ASSERT(os->isUserdata(getId<World>(), -1));
		}
	}
};

// =====================================================================

struct Body
{
	static int getMassCenter(OS * os, int params, int, int, void*)
	{
		GET_SELF(b2Body);
		b2MassData massData;
		self->GetMassData(&massData);
		Box2dValue<b2Vec2>::push(os, massData.center);
		return 1;
	}

	static int setMassCenter(OS * os, int params, int, int, void*)
	{
		GET_SELF(b2Body);
		GET_ARG(1, b2Vec2);
		b2MassData massData;
		self->GetMassData(&massData);
		massData.center = Box2dValue<b2Vec2>::to(os, -params);
		self->SetMassData(&massData);
		return 0;
	}

	static int setMass(OS * os, int params, int, int, void*)
	{
		GET_SELF(b2Body);
		b2MassData massData;
		self->GetMassData(&massData);
		massData.mass = Box2dValue<float32>::to(os, -params);
		self->SetMassData(&massData);
		return 0;
	}

	static int setInertia(OS * os, int params, int, int, void*)
	{
		GET_SELF(b2Body);
		b2MassData massData;
		self->GetMassData(&massData);
		massData.I = Box2dValue<float32>::to(os, -params);
		self->SetMassData(&massData);
		return 0;
	}

	static int setPosition(OS * os, int params, int, int, void*)
	{
		GET_SELF(b2Body);
		b2Transform xf = self->GetTransform();
		xf.p = Box2dValue<b2Vec2>::to(os, -params);
		self->SetTransform(xf.p, xf.q.GetAngle());
		return 0;
	}

	static int setAngle(OS * os, int params, int, int, void*)
	{
		GET_SELF(b2Body);
		b2Transform xf = self->GetTransform();
		self->SetTransform(xf.p, os->toFloat(-params));
		return 0;
	}

	static b2CircleShape * toCircleShape(OS * os, int offs)
	{
		b2CircleShape * shape = new (os->malloc(sizeof(b2CircleShape) OS_DBG_FILEPOS)) b2CircleShape();
		
		os->getProperty(offs, "radius", false); // optional
		shape->m_radius = toBox2dMetric(os->popFloat(fromBox2dMetric(shape->m_radius)));
		
		os->getProperty(offs, "center", false); // optional
		if(os->isNull()){
			os->pop();
			os->getProperty(offs, "position", false); // optional
		}
		if(os->isNull()){
			os->pop();

			os->getProperty(offs, "x", false); // optional
			shape->m_p.x = toBox2dMetric(os->popFloat(fromBox2dMetric(shape->m_p.x)));
			
			os->getProperty(offs, "y", false); // optional
			shape->m_p.y = toBox2dMetric(os->popFloat(fromBox2dMetric(shape->m_p.y)));
		}else{
			shape->m_p = Box2dValue<b2Vec2>::to(os, -1);
			os->pop();
		}
		return shape;
	}

	static b2CircleShape * toAutoCircleShape(OS * os, int offs)
	{
		return toCircleShape(os, offs);
	}

	static b2EdgeShape * toEdgeShape(OS * os, int offs)
	{
		b2EdgeShape * shape = new (os->malloc(sizeof(b2EdgeShape) OS_DBG_FILEPOS)) b2EdgeShape();
		
		os->getProperty(offs, "radius", false); // optional
		shape->m_radius = toBox2dMetric(os->popFloat(fromBox2dMetric(shape->m_radius)));
		
		os->getProperty(offs, "vertex1", false); // optional
		if(os->isNull()) return error(shape, os, "vertex1 expected by edge shape");
		shape->m_vertex1 = Box2dValue<b2Vec2>::to(os, -1);
		os->pop();

		os->getProperty(offs, "vertex2", false); // optional
		if(os->isNull()) return error(shape, os, "vertex2 expected by edge shape");
		shape->m_vertex2 = Box2dValue<b2Vec2>::to(os, -1);
		os->pop();

		os->getProperty(offs, "vertex0", false); // optional
		if(!os->isNull()){
			shape->m_vertex0 = Box2dValue<b2Vec2>::to(os, -1);
			shape->m_hasVertex0 = true;
		}
		os->pop();

		os->getProperty(offs, "vertex3", false); // optional
		if(!os->isNull()){
			shape->m_vertex3 = Box2dValue<b2Vec2>::to(os, -1);
			shape->m_hasVertex3 = true;
		}
		os->pop();

		return shape;
	}
		
	static b2PolygonShape * toPolygonShape(OS * os, int offs)
	{
		b2PolygonShape * shape = new (os->malloc(sizeof(b2PolygonShape) OS_DBG_FILEPOS)) b2PolygonShape();

		os->getProperty(offs, "radius", false); // optional
		shape->m_radius = toBox2dMetric(os->popFloat(fromBox2dMetric(shape->m_radius)));
		
		os->getProperty(offs, "vertices", false); // optional
		if(os->isNull()){
			os->pop();
			os->getProperty(offs, "points", false); // optional
		}
		if(!os->isArray()) return error(shape, os, "array of vertices expected by polygon shape");
		int count = os->getLen();
		if(count < 1) return error(shape, os, "not clear array of vertices expected by polygon shape");
		if(count > b2_maxPolygonVertices) return error(shape, os, OS::String::format(os, "too much vertices for polygon shape, max: %d", b2_maxPolygonVertices).toChar());

		b2Vec2 vertices[b2_maxPolygonVertices];
		for(int i = 0; i < count; i++){
			os->pushStackValue();
			os->pushNumber(i);
			os->getProperty();
			vertices[i] = Box2dValue<b2Vec2>::to(os, -1);
			os->pop();
		}
		shape->Set(vertices, count);
		os->pop(); // vertices

		return shape;
	}
	
	static b2PolygonShape * toAutoPolygonShape(OS * os, int offs)
	{
		b2PolygonShape * shape = new (os->malloc(sizeof(b2PolygonShape) OS_DBG_FILEPOS)) b2PolygonShape();

		if(!os->isArray(offs)) return error(shape, os, "array of shape expected");
		int count = os->getLen();
		if(count < 1) return error(shape, os, "not clear array of shape expected");
		if(count > b2_maxPolygonVertices) return error(shape, os, OS::String::format(os, "too much vertices for polygon shape, max: %d", b2_maxPolygonVertices).toChar());

		b2Vec2 vertices[b2_maxPolygonVertices];
		for(int i = 0; i < count; i++){
			os->pushStackValue(offs);
			os->pushNumber(i);
			os->getProperty();
			vertices[i] = Box2dValue<b2Vec2>::to(os, -1);
			os->pop();
		}
		shape->Set(vertices, count);

		return shape;
	}
	
	static b2LoopShape * toLoopShape(OS * os, int offs)
	{
		b2LoopShape * shape = new (os->malloc(sizeof(b2LoopShape) OS_DBG_FILEPOS)) b2LoopShape();

		os->getProperty(offs, "radius", false); // optional
		shape->m_radius = toBox2dMetric(os->popFloat(fromBox2dMetric(shape->m_radius)));
		
		os->getProperty(offs, "vertices", false); // optional
		if(os->isNull()){
			os->pop();
			os->getProperty(offs, "points", false); // optional
		}
		if(!os->isArray()) return error(shape, os, "array of vertices expected by loop shape");
		int count = os->getLen();
		if(count < 1) return error(shape, os, "not clear array of vertices expected by loop shape");

		b2Vec2 * vertices = (b2Vec2*)os->malloc(sizeof(b2Vec2)*count OS_DBG_FILEPOS);
		for(int i = 0; i < count; i++){
			os->pushStackValue();
			os->pushNumber(i);
			os->getProperty();
			vertices[i] = Box2dValue<b2Vec2>::to(os, -1);
			os->pop();
		}
		shape->Create(vertices, count);
		os->free(vertices);
		os->pop(); // vertices

		return shape;
	}

	static b2Shape * toShape(OS * os, int offs)
	{
		os->getProperty(offs, "type", false); // optional
		OS::String type = os->popString();
		if(type == "circle"){
			return toCircleShape(os, offs);
		}else if(type == "edge"){
			return toEdgeShape(os, offs);
		}else if(type == "polygon"){
			return toPolygonShape(os, offs);
		}else if(type == "loop"){
			return toLoopShape(os, offs);
		}
		os->getProperty(offs, "radius", false); // optional
		if(!os->isNull()){
			os->pop();
			return toAutoCircleShape(os, offs);
		}
		return toAutoPolygonShape(os, offs);
		// os->triggerError(OS_E_ERROR, "shape type expected");
		// return NULL;
	}

	static void populateFixtureDef(b2FixtureDef& def, OS * os, int offs)
	{
		os->getProperty(offs, "friction", false); // optional
		def.friction = os->popFloat(def.friction);

		os->getProperty(offs, "bounce", false); // optional
		def.restitution = os->popFloat(def.restitution);

		os->getProperty(offs, "density", false); // optional
		def.density = os->popFloat(def.density);

		os->getProperty(offs, "sensor", false); // optional
		def.isSensor = os->popBool(def.isSensor);

		os->getProperty(offs, "categoryBits", false); // optional
		def.filter.categoryBits = os->popInt(def.filter.categoryBits);

		os->getProperty(offs, "maskBits", false); // optional
		def.filter.maskBits = os->popInt(def.filter.maskBits);

		os->getProperty(offs, "groupIndex", false); // optional
		def.filter.groupIndex = os->popInt(def.filter.groupIndex);
	}

	static void createFixture(b2Body * self, OS * os, int offs)
	{
		// OS_ASSERT(os->isObject(
		os->getProperty(offs, "shape", false); // optional
		if(os->isObject()){ // fixture
			b2FixtureDef def;
			def.shape = toShape(os, -1); os->pop();
			if(!def.shape) return;
			
			populateFixtureDef(def, os, offs);
			
			self->CreateFixture(&def);

			def.shape->~b2Shape();
			os->free((void*)def.shape);
			def.shape = NULL;
		}else if(os->isArray()){
			b2FixtureDef def;
			def.shape = toAutoPolygonShape(os, -1);
			if(!def.shape) return;
			os->pop();
			
			populateFixtureDef(def, os, offs);
			
			self->CreateFixture(&def);

			def.shape->~b2Shape();
			os->free((void*)def.shape);
			def.shape = NULL;
		}else{ // shape
			os->pop();
			offs = os->getAbsoluteOffs(offs);
			os->getProperty(offs, "shapes", false); // optional
			if(os->isArray()){
				int count = os->getLen();
				for(int i = 0; i < count; i++){
					os->pushStackValue();
					os->pushNumber(i);
					os->getProperty();
					os->clone(offs);
					os->pushStackValue();
					os->deleteProperty("shapes", false, false);
					os->pushStackValue();
					os->pushStackValue(-3);
					os->setProperty("shape", false, false);
					createFixture(self, os, -1);
					os->pop(2);
				}
				os->pop();
			}else{
				os->pop();
				b2Shape * shape = toShape(os, offs);
				float density = os->toFloat(offs+1);
				self->CreateFixture(shape, density);
				shape->~b2Shape();
				os->free(shape);
			}
		}
	}

	static int createFixture(OS * os, int params, int, int, void*)
	{
		GET_SELF(b2Body);
		if(os->isObject(-params)){
			createFixture(self, os, -params);
			return 0;
		}
		os->triggerError(OS_E_ERROR, "error arguments");
		return 0;
	}

	static int getWorld(OS * os, int params, int, int, void*)
	{
		GET_SELF(b2Body);
		Box2dValue<World*>::push(os, World::toWorld(self->GetWorld()));
		return 1;
	}

	static void init(OS * os)
	{
		OS::FuncDef funcs[] = {
			{"createFixture", createFixture},
			// GET_METHOD_1_NOT_CONST(b2Body, b2Fixture*, createFixture, CreateFixture, const b2FixtureDef*),
			// GET_METHOD_2_NOT_CONST(b2Body, b2Fixture*, createFixtureByShape, CreateFixture, const b2Shape*, float32),
			VOID_METHOD_1(b2Body, destroyFixture, DestroyFixture, b2Fixture*),
			VOID_METHOD_2(b2Body, setTransform, SetTransform, const b2Vec2&, float32),
			GET_METHOD(b2Body, const b2Transform&, transform, GetTransform),
			GET_METHOD(b2Body, const b2Vec2&, position, GetPosition),
			{"__set@position", setPosition},
			GET_METHOD(b2Body, float32, angle, GetAngle),
			{"__set@angle", setAngle},
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
			{"__set@mass", setMass},
			GET_METHOD(b2Body, float32, inertia, GetInertia),
			{"__set@inertia", setInertia},
			{"__get@massCenter", getMassCenter},
			{"__set@massCenter", setMassCenter},
			// {"__get@massData", getMassData},
			// SET_METHOD(b2Body, const b2MassData*, massData, SetMassData),
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
			// GET_METHOD(b2Body, const b2JointEdge*, jointList, GetJointList),
			// GET_METHOD(b2Body, const b2ContactEdge*, contactList, GetContactList),
			GET_METHOD(b2Body, const b2Body*, next, GetNext),
			// GET_METHOD(b2Body, const b2World*, world, GetWorld),
			{"__get@world", getWorld},
			{}
		};

		initClass<b2Body>(os, funcs);
	}
};

}

using namespace Box2dObjectScript;

void World::createBodyFixture(b2Body * body, OS * os, int offs)
{
	Body::createFixture(body, os, offs);
}

void initBox2d(OS * os)
{
	World::init(os);
	Body::init(os);
}

