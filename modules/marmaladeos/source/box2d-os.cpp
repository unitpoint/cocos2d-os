#include "box2d-os.h"
#include "Box2D\Box2D.h"

namespace Box2dObjectScript {

template <class T> int getClassId(){ static int id = (int)&id; return id; }
template <class T> int getId(){ static int id = (int)&id; return id; }

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

// =====================================================================

template <class T> 
struct ToValue
{
	typedef T type;
};

template <> 
struct ToValue <const b2Vec2&>
{
	typedef b2Vec2 type;
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
struct PushValue <const b2Color&>
{
	typedef const b2Color * type;

	static type arg(const b2Color& val){ return &val; }
};

template <> 
struct PushValue <const b2Transform&>
{
	typedef const b2Transform * type;

	static type arg(const b2Transform& val){ return &val; }
};

template <> 
struct PushValue <const b2Fixture*>
{
	typedef b2Fixture * type;

	static type arg(const b2Fixture * val){ return (b2Fixture*)val; }
};

template <> 
struct PushValue <const b2JointEdge*>
{
	typedef b2JointEdge * type;

	static type arg(const b2JointEdge * val){ return (b2JointEdge*)val; }
};

template <> 
struct PushValue <const b2ContactEdge*>
{
	typedef b2ContactEdge * type;

	static type arg(const b2ContactEdge * val){ return (b2ContactEdge*)val; }
};

template <> 
struct PushValue <const b2Manifold*>
{
	typedef b2Manifold * type;

	static type arg(const b2Manifold * val){ return (b2Manifold*)val; }
};

template <> 
struct PushValue <const b2Contact*>
{
	typedef b2Contact * type;

	static type arg(const b2Contact * val){ return (b2Contact*)val; }
};

template <> 
struct PushValue <const b2World*>
{
	typedef b2World * type;

	static type arg(const b2World * val){ return (b2World*)val; }
};

template <> 
struct PushValue <const b2Body*>
{
	typedef b2Body * type;

	static type arg(const b2Body * val){ return (b2Body*)val; }
};

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

template <class T, class FieldType, FieldType T::*FieldPtr> 
int setField(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		data->*FieldPtr = toValue<typename ToValue<FieldType>::type>(os, -params);
	}
	return 0;
}

#define TO_STR(t) #t

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

template <class T, typename FieldType, typename Arg1Type, typename Arg2Type, FieldType(T::*F)(Arg1Type, Arg2Type)> 
int getFieldByMethodArgs2(OS * os, int params, int, int, void*)
{
	T * data = (T*)os->toUserdata(getId<T>(), -params-1);
	if(data){
		pushValue<typename PushValue<FieldType>::type>(os, 
			PushValue<FieldType>::arg( (data->*F)(toValue<typename ToValue<Arg1Type>::type>(os, -params), 
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

#define SET_FIELD(T, FieldType, FieldName)  {"__set@"#FieldName, setField<T, FieldType, & T::FieldName>}
#define GET_FIELD(T, FieldType, FieldName)  {"__get@"#FieldName, getField<T, FieldType, & T::FieldName>}

#define SET_FIELD_READONLY(T, FieldType, FieldName)  {"__set@"#FieldName, setFieldReadonly<T, FieldType, & T::FieldName>}

#define GET_METHOD(T, FieldType, FieldName, MethodName)  {"__get@"#FieldName, getFieldByMethod<T, FieldType, & T::MethodName>}
#define GET_METHOD_1(T, FieldType, FieldName, MethodName, Arg1Type)  {#FieldName, getFieldByMethodArg1<T, FieldType, Arg1Type, & T::MethodName>}
#define GET_METHOD_1_NOT_CONST(T, FieldType, FieldName, MethodName, Arg1Type)  {#FieldName, getFieldByNotConstMethodArg1<T, FieldType, Arg1Type, & T::MethodName>}
#define GET_METHOD_2(T, FieldType, FieldName, MethodName, Arg1Type, Arg2Type)  {#FieldName, getFieldByMethodArgs2<T, FieldType, Arg1Type, Arg2Type, & T::MethodName>}

#define SET_METHOD(T, FieldType, FieldName, MethodName)  {"__set@"#FieldName, setFieldByMethod<T, FieldType, & T::MethodName>}

#define VOID_METHOD(T, Name, MethodName)  {#Name, voidMethod<T, & T::MethodName>}
#define VOID_METHOD_1(T, Name, MethodName, Arg1Type)  {#Name, voidMethodArg1<T, Arg1Type, & T::MethodName>}
#define VOID_METHOD_2(T, Name, MethodName, Arg1Type, Arg2Type)  {#Name, voidMethodArgs2<T, Arg1Type, Arg2Type, & T::MethodName>}

#define SYNTHESIZE(T, FieldType, FieldName) \
			SET_FIELD(T, FieldType, FieldName), \
			GET_FIELD(T, FieldType, FieldName)

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

template <> void osProxiDestructor<b2Joint>(OS * os, void * data, void * user_param)
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
	return (int)val->userData;
}

template <> void setValueId<b2BodyDef>(OS * os, b2BodyDef * val)
{
	val->userData = (void*)os->getValueId();
}

// =====================================================================

template <> int getValueId<b2FixtureDef>(OS * os, b2FixtureDef * val)
{
	return (int)val->userData;
}

template <> void setValueId<b2FixtureDef>(OS * os, b2FixtureDef * val)
{
	val->userData = (void*)os->getValueId();
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

template <> int getValueId<b2ContactEdge>(OS * os, b2ContactEdge * val)
{
	return 0;
}

template <> void setValueId<b2ContactEdge>(OS * os, b2ContactEdge * val)
{
}

// =====================================================================

template <> int getValueId<b2ManifoldPoint>(OS * os, b2ManifoldPoint * val)
{
	return 0;
}

template <> void setValueId<b2ManifoldPoint>(OS * os, b2ManifoldPoint * val)
{
}

// =====================================================================

template <class T> void pushObject(OS * os, T * val)
{
	int valueId = getValueId(os, val);
	if(valueId){
		os->pushValueById(valueId);
		if(!os->isNull()){
			OS_ASSERT(os->toUserdata(getId<T>()));
			return;
		}
		os->pop();
	}
	os->pushUserPointer(getId<T>(), val, osProxiDestructor<T>);
	setValueId(os, val);
	os->pushStackValue();
	os->getGlobal(TO_STR(T));
	OS_ASSERT(os->toUserdata(getClassId<T>()));
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

template <> void pushValue<b2Vec2>(OS * os, b2Vec2 val)
{
	pushPointAsObject(os, val);
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

template <> void pushValue<const b2Color*>(OS * os, const b2Color * val)
{
	os->newArray(3);

	os->pushStackValue();
	os->pushNumber(val->r);
	os->addProperty();

	os->pushStackValue();
	os->pushNumber(val->g);
	os->addProperty();

	os->pushStackValue();
	os->pushNumber(val->b);
	os->addProperty();
}

template <> void pushValue<const b2Transform *>(OS * os, const b2Transform * val)
{
	os->pushNull();
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

template <> b2World* toValue<b2World*>(OS * os, int offs)
{
	b2World * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2World*>(OS * os, b2World* val)
{
	pushObject(os, val);
}

class World: public b2World, b2DestructionListener, b2ContactFilter, b2ContactListener, b2Draw, b2QueryCallback, b2RayCastCallback
{
public:

	OS * os;
	int osId; // weak ref to ObjectScript value

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
		OS_ASSERT(os->toUserdata(getId<b2World>()));
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
			pushValue(os, &color);
			pushValue(os, false);
			os->call(3, 0);
		}
	}

	/// Draw a solid closed polygon provided in CCW order.
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if(getFunction("drawPolygon")){
			pushVertices(os, vertices, vertexCount);
			pushValue(os, &color);
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
			pushValue(os, &color);
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
			pushValue(os, &color);
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
			pushValue(os, &color);
			os->call(5, 0);
		}
	}

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	void DrawTransform(const b2Transform& xf)
	{
		if(getFunction("drawTransform")){
			pushValue(os, &xf);
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
		b2JointDef * def;
		if(toObject(os, world, -params-1) && toObject(os, def, -params)){
			pushObject(os, world->CreateJoint(def));
			return 1;
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
			world->QueryAABB(world, aabb);
		}
		return 0;
	}

	static int rayCast(OS * os, int params, int, int, void*)
	{
		if(params < 3) return 0;
		World * world;
		if(toObject(os, world, -params-1) && os->isFunction(-params)){
			os->pushStackValue(-params); // get it at top of stack for ReportFixture
			world->RayCast(world, toVec2(os, -params+1), toVec2(os, -params+2));
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
			pushObject(os, world->GetJointList());
			return 1;
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
		new (os->pushUserdata(getId<b2World>(), sizeof(World), destructor)) World(os, gravity, sleep);
		os->pushStackValue(-1);
		os->getGlobal("b2World");
		OS_ASSERT(os->toUserdata(getClassId<b2World>()));
		os->setPrototype(getId<b2World>());
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
		os->pushUserdata(getClassId<b2World>(), 0);
		os->setFuncs(list);
		os->setNulls(nulls);
		os->setProperty();
	}
};

template <> int getValueId<b2World>(OS * os, b2World * val)
{
	return ((World*)val)->osId;
}

template <> void setValueId<b2World>(OS * os, b2World * val)
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
		OS_ASSERT(os->toUserdata(getClassId<b2BodyDef>()));
		os->setPrototype(getId<b2BodyDef>());
		return 1;
	}

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
			{"__construct", BodyDef::create},
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
			SYNTHESIZE_READONLY(b2JointEdge, b2Joint*, joint),
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

template <> b2Body* toValue<b2Body*>(OS * os, int offs)
{
	b2Body * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Body*>(OS * os, b2Body* val)
{
	pushObject(os, val);
}

struct JointDef
{
	static void destructor(OS * os, void * data, void * user_param)
	{
		b2JointDef * val = (b2JointDef*)data;
		val->~b2JointDef();
	}

	static int create(OS * os, int params, int, int, void*)
	{
		b2JointDef * def = new (os->pushUserdata(getId<b2JointDef>(), sizeof(b2JointDef), destructor)) b2JointDef();
		def->userData = (void*)os->getValueId();
		os->pushStackValue(-1);
		os->getGlobal("b2JointDef");
		OS_ASSERT(os->toUserdata(getClassId<b2JointDef>()));
		os->setPrototype(getId<b2JointDef>());
		return 1;
	}

	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			SYNTHESIZE(b2JointDef, b2JointType, type),
			SYNTHESIZE(b2JointDef, b2Body*, bodyA),
			SYNTHESIZE(b2JointDef, b2Body*, bodyB),
			SYNTHESIZE(b2JointDef, bool, collideConnected),
			{"__construct", JointDef::create},
			{}
		};

		os->pushGlobals();
		os->pushString("b2JointDef");
		os->pushUserdata(getClassId<b2JointDef>(), 0);
		os->setFuncs(list);
		os->setProperty();
	}
};

// =====================================================================

template <> b2Joint* toValue<b2Joint*>(OS * os, int offs)
{
	b2Joint * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Joint*>(OS * os, b2Joint* val)
{
	pushObject(os, val);
}

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
		OS_ASSERT(os->toUserdata(getClassId<b2MassData>()));
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

template <> const b2FixtureDef* toValue<const b2FixtureDef*>(OS * os, int offs)
{
	b2FixtureDef * val;
	toObject(os, val, offs);
	return val;
}

template <> void pushValue<b2FixtureDef*>(OS * os, b2FixtureDef* val)
{
	pushObject(os, val);
}

template <> b2Fixture* toValue<b2Fixture*>(OS * os, int offs)
{
	b2Fixture * val;
	return toObject(os, val, offs);
}

template <> void pushValue<b2Fixture*>(OS * os, b2Fixture* val)
{
	pushObject(os, val);
}

template <> const b2Shape* toValue<const b2Shape*>(OS * os, int offs)
{
	const b2Shape * val;
	return toObject(os, val, offs);
}

struct Body
{
	static int GetMassData(OS * os, int params, int, int, void*)
	{
		b2Body * body = (b2Body*)os->toUserdata(getId<b2Body>(), -params-1);
		if(body){
			b2MassData * data = MassData::pushDefault(os);
			body->GetMassData(data);
			// pushValue(os, data); - already is stack
			return 1;
		}
		return 0;
	}

	static void init(OS * os)
	{
		OS::FuncDef list[] = {
			GET_METHOD_1_NOT_CONST(b2Body, b2Fixture*, createFixture, CreateFixture, const b2FixtureDef*),
			GET_METHOD_2(b2Body, b2Fixture*, createFixtureByShape, CreateFixture, const b2Shape*, float32),
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
			{"__get@massData", GetMassData},
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

using namespace Box2dObjectScript;

void osExportBox2d(OS * os)
{
	World::init(os);
	BodyDef::init(os);
	Body::init(os);
	ManifoldPoint::init(os);
}

