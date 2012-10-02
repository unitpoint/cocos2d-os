#include "box2d-os.h"
#include "Box2D\Box2D.h"
#include "os-api-helper.h"

namespace ObjectScript {

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

OS_DECL_CTYPE(b2Vec2);
OS_DECL_CTYPE(b2Transform);

OS_DECL_CTYPE(b2CircleShape);
OS_DECL_CTYPE(b2EdgeShape);
OS_DECL_CTYPE(b2LoopShape);
OS_DECL_CTYPE(b2PolygonShape);

OS_DECL_CTYPE(b2RopeJoint);
OS_DECL_CTYPE(b2RevoluteJoint);
OS_DECL_CTYPE(b2PulleyJoint);
OS_DECL_CTYPE(b2PrismaticJoint);
OS_DECL_CTYPE(b2MouseJoint);
OS_DECL_CTYPE(b2GearJoint);
OS_DECL_CTYPE(b2FrictionJoint);
OS_DECL_CTYPE(b2DistanceJoint);
OS_DECL_CTYPE(b2WheelJoint);
OS_DECL_CTYPE(b2WeldJoint);

OS_DECL_CTYPE(b2Fixture);
OS_DECL_CTYPE(b2Contact);
OS_DECL_CTYPE(b2ContactImpulse);
OS_DECL_CTYPE(b2Body);
OS_DECL_CTYPE(b2BodyType);
OS_DECL_CTYPE(b2Manifold);

class World;
OS_DECL_CTYPE_NAME(World, "b2World");

// =====================================================================

template <>
struct CtypeValue<b2BodyType>
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
struct CtypeValue<b2JointType>
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
struct CtypeValue<b2Vec2>
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
struct CtypeValue<b2Color>
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
struct CtypeValue<b2Transform>
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
struct CtypeValue<b2Profile>
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
struct Box2dObject
{
};

template <class T>
struct Box2dObject<T*>
{
	typedef typename RemoveConst<T>::type * type;

	static bool isValid(type obj){ return obj != NULL; }

	static type to(type val){ return (type)val; }
	static type to(const typename RemoveConst<T>::type * val){ return (type)val; }

	static type to(OS * os, int offs)
	{
		return (type)os->toUserdata(getInstanceId<T>(), offs);
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
				OS_ASSERT(to(os, -1));
				return;
			}
			os->pop();
		}
		os->pushUserPointer(getInstanceId<T>(), val, osObjectDestructor<T>);
		setValueId(os, val);
		os->pushStackValue();
		os->getGlobal(getCtypeName<T>());
		OS_ASSERT(os->isUserdata(getCtypeId<T>(), -1));
		os->setPrototype(getInstanceId<T>());
	}
};

// =====================================================================

template <> struct CtypeValue<b2Body*>: public Box2dObject<b2Body*> {};
// template <> struct CtypeValue<const b2Body*>: public Box2dObject<b2Body*> {};

// =====================================================================

template <> struct CtypeValue<b2Fixture*>: public Box2dObject<b2Fixture*> {};
// template <> struct CtypeValue<const b2Fixture*>: public Box2dObject<b2Fixture*> {};

// =====================================================================

template <class T>
struct Box2dSimpleObject
{
};

template <class T>
struct Box2dSimpleObject<T*>
{
	typedef typename RemoveConst<T>::type * type;

	static bool isValid(type obj){ return obj != NULL; }

	static type to(type val){ return (type)val; }
	static type to(const typename RemoveConst<T>::type * val){ return (type)val; }

	static type to(OS * os, int offs)
	{
		return (type)os->toUserdata(getInstanceId<T>(), offs);
	}

	static void push(OS * os, type val)
	{
		if(!val){
			os->pushNull();
			return;
		}
		os->pushUserPointer(getInstanceId<T>(), val, osObjectDestructor<T>);
		os->pushStackValue();
		os->getGlobal(getCtypeName<T>());
		OS_ASSERT(os->isUserdata(getCtypeId<T>(), -1));
		os->setPrototype(getInstanceId<T>());
	}
};

// =====================================================================

template <> struct CtypeValue<b2Contact*>: public Box2dSimpleObject<b2Contact*> {};
// template <> struct CtypeValue<const b2Contact*>: public Box2dSimpleObject<b2Contact*> {};

// =====================================================================

template <> struct CtypeValue<b2ContactImpulse*>: public Box2dSimpleObject<b2ContactImpulse*> {};
// template <> struct CtypeValue<const b2ContactImpulse*>: public Box2dSimpleObject<b2ContactImpulse*> {};

// =====================================================================

template <> struct CtypeValue<b2Manifold*>: public Box2dSimpleObject<b2Manifold*> {};
// template <> struct CtypeValue<const b2Manifold*>: public Box2dSimpleObject<b2Manifold*> {};

// =====================================================================

void pushXY(OS * os, const b2Vec2& p)
{
	pushCtypeValue(os, fromBox2dMetric(p.x));
	pushCtypeValue(os, fromBox2dMetric(p.y));
}

void pushVertices(OS * os, const b2Vec2* vertices, int count)
{
	os->newArray(count);
	for(int i = 0; i < count; i++){
		os->pushStackValue();
		pushCtypeValue(os, vertices[i]);
		os->addProperty();
	}
}

// =====================================================================

template <class T> void clearUserdata(OS * os, T * val)
{
	os->pushValueById((int)val->GetUserData());
	os->clearUserdata(getInstanceId<T>());
	os->pop();
}

// =====================================================================

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

template <>
struct CtypeValue<World*>
{
	typedef World * type;

	static bool isValid(type obj){ return obj != NULL; }

	static type to(World * val){ return (type)val; }
	static type to(const World * val){ return (type)val; }

	static type to(OS * os, int offs)
	{
		return (type)os->toUserdata(getInstanceId<World>(), offs);
	}

	static void push(OS * os, type val);
};

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
		OS_ASSERT(os->isUserdata(getInstanceId<World>(), -1));
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
			pushCtypeValue(os, fixtureA);
			pushCtypeValue(os, fixtureB);
			os->call(2, 1);
			return os->popBool();
		}
		return true;
	}

	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact)
	{ 
		if(getFunction("beginContact")){
			pushCtypeValue(os, contact);
			os->call(1, 0);
		}
	}

	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact)
	{ 
		if(getFunction("endContact")){
			pushCtypeValue(os, contact);
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
			pushCtypeValue(os, contact);
			pushCtypeValue(os, oldManifold);
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
			pushCtypeValue(os, contact);
			pushCtypeValue(os, impulse);
			os->call(2, 0);
		}
	}

	/// Draw a closed polygon provided in CCW order.
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if(getFunction("drawPolygon")){
			pushVertices(os, vertices, vertexCount);
			pushCtypeValue(os, color);
			pushCtypeValue(os, false);
			os->call(3, 0);
		}
	}

	/// Draw a solid closed polygon provided in CCW order.
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if(getFunction("drawPolygon")){
			pushVertices(os, vertices, vertexCount);
			pushCtypeValue(os, color);
			pushCtypeValue(os, true);
			os->call(3, 0);
		}
	}

	/// Draw a circle.
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		if(getFunction("drawCircle")){
			pushXY(os, center);
			pushCtypeValue(os, radius);
			pushCtypeValue(os, color);
			pushCtypeValue(os, false);
			os->call(5, 0);
		}
	}
	
	/// Draw a solid circle.
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		if(getFunction("drawSolidCircle")){
			pushXY(os, center);
			pushCtypeValue(os, radius);
			pushCtypeValue(os, color);
			pushCtypeValue(os, true);
			os->call(5, 0);
		}
	}
	
	/// Draw a line segment.
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		if(getFunction("drawSegment")){
			pushXY(os, p1);
			pushXY(os, p2);
			pushCtypeValue(os, color);
			os->call(5, 0);
		}
	}

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	void DrawTransform(const b2Transform& xf)
	{
		if(getFunction("drawTransform")){
			pushCtypeValue(os, xf);
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
		pushCtypeValue(os, fixture);
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
		pushCtypeValue(os, fixture);
		pushXY(os, point);
		pushXY(os, normal);
		pushCtypeValue(os, fraction);
		os->call(6, 1);
		return os->popFloat(1.0f);
	}

	static void createBodyFixture(b2Body*, OS*, int offs);

	static int createBody(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(World*);
		if(!os->isObject(-params)) return error(os, "body def object expected");

		b2BodyDef def;
		int offs = os->getAbsoluteOffs(-params);

		os->getProperty(offs, "type", false); // optional because of we handle error next line of code
		if(os->isNull()) return error(os, "type expected by body def");
		def.type = CtypeValue<b2BodyType>::to(os, -1);
		os->pop();

		os->getProperty(offs, "position", false); // optional
		if(os->isNull()){
			os->pop();

			os->getProperty(offs, "x", false); // optional
			def.position.x = toBox2dMetric(os->popFloat(fromBox2dMetric(def.position.x)));
			
			os->getProperty(offs, "y", false); // optional
			def.position.y = toBox2dMetric(os->popFloat(fromBox2dMetric(def.position.y)));
		}else{
			def.position = CtypeValue<b2Vec2>::to(os, -1);
			os->pop();
		}
		// def.position.x *= self->metricScale;
		// def.position.y *= self->metricScale;

		os->getProperty(offs, "angle", false); // optional
		def.angle = os->popFloat(def.angle);

		os->getProperty(offs, "linearVelocity", false); // optional
		def.linearVelocity = os->isNull() ? def.linearVelocity : CtypeValue<b2Vec2>::to(os, -1);
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
		pushCtypeValue(os, body);

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
		OS_GET_SELF(World*);
		OS_GET_ARG(1, b2Body*);
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
		OS_GET_SELF(World*);
		if(!os->isObject(-params)) return error(os, "joint def object expected");
		int offs = os->getAbsoluteOffs(-params);

		os->getProperty(offs, "type", false); // optional because of we handle error next line of code
		if(os->isNull()) return error(os, "type expected by joint def");
		b2JointType type = CtypeValue<b2JointType>::to(os, -1); os->pop();
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
		OS_GET_SELF(World*);
		OS_GET_ARG(1, b2Joint*);
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
		b2Vec2 gravity = params > 0 ? CtypeValue<b2Vec2>::to(os, -params) : b2Vec2(0, 9.8f);
		bool sleep = os->toBool(-params+1, true);
		new (os->pushUserdata(getInstanceId<World>(), sizeof(World), destructor)) World(os, gravity, sleep);
		// os->retainValueById(os->getValueId());
		os->pushStackValue();
		os->getGlobal(getCtypeName<World>());
		OS_ASSERT(os->isUserdata(getCtypeId<World>(), -1));
		os->setPrototype(getInstanceId<World>());
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
			OS_VOID_METHOD_3_SPEC(World, step, b2World, Step, float32, int32, int32),
			OS_VOID_METHOD_SPEC(World, clearForces, b2World, ClearForces),
			OS_VOID_METHOD_SPEC(World, drawDebugData, b2World, DrawDebugData),
			// void QueryAABB(b2QueryCallback* callback, const b2AABB& aabb) const;
			// void RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2) const;
			OS_GET_METHOD_SPEC(World, const b2Body*, bodyList, b2World, GetBodyList),
			// OS_GET_METHOD_SPEC(World, const b2Joint*, jointList, b2World, GetJointList),
			OS_GET_METHOD_SPEC(World, const b2Contact*, contactList, b2World, GetContactList),
			OS_SET_METHOD_SPEC(World, bool, warmStarting, b2World, SetWarmStarting),
			OS_SET_METHOD_SPEC(World, bool, continuousPhysics, b2World, SetContinuousPhysics),
			OS_SET_METHOD_SPEC(World, bool, subStepping, b2World, SetSubStepping),
			OS_GET_METHOD_SPEC(World, int32, proxyCount, b2World, GetProxyCount),
			OS_GET_METHOD_SPEC(World, int32, bodyCount, b2World, GetBodyCount),
			OS_GET_METHOD_SPEC(World, int32, jointCount, b2World, GetJointCount),
			OS_GET_METHOD_SPEC(World, int32, contactCount, b2World, GetContactCount),
			OS_GET_METHOD_SPEC(World, int32, treeHeight, b2World, GetTreeHeight),
			OS_GET_METHOD_SPEC(World, int32, treeBalance, b2World, GetTreeBalance),
			OS_GET_METHOD_SPEC(World, float32, treeQuality, b2World, GetTreeQuality),
			OS_GET_METHOD_SPEC(World, b2Vec2, gravity, b2World, GetGravity),
			OS_SET_METHOD_SPEC(World, const b2Vec2&, gravity, b2World, SetGravity),
			OS_GET_METHOD_SPEC(World, bool, isLocked, b2World, IsLocked),
			OS_GET_METHOD_SPEC(World, bool, autoClearForces, b2World, GetAutoClearForces),
			OS_SET_METHOD_SPEC(World, bool, autoClearForces, b2World, SetAutoClearForces),
			OS_GET_METHOD_SPEC(World, const b2Profile&, profile, b2World, GetProfile),
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
		os->pushString(getCtypeName<World>());
		os->pushUserdata(getCtypeId<World>(), 0);
		os->setFuncs(funcs);
		os->setNulls(nulls);
		os->setProperty();
	}
};

void CtypeValue<World*>::push(OS * os, type val)
{
	if(!val){
		os->pushNull();
		return;
	}
	os->pushValueById(val->osId);
	if(!os->isNull()){
		OS_ASSERT(to(os, -1));
	}
}

// =====================================================================

struct Body
{
	static int getMassCenter(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(b2Body*);
		b2MassData massData;
		self->GetMassData(&massData);
		CtypeValue<b2Vec2>::push(os, massData.center);
		return 1;
	}

	static int setMassCenter(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(b2Body*);
		OS_GET_ARG(1, b2Vec2);
		b2MassData massData;
		self->GetMassData(&massData);
		massData.center = CtypeValue<b2Vec2>::to(os, -params);
		self->SetMassData(&massData);
		return 0;
	}

	static int setMass(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(b2Body*);
		b2MassData massData;
		self->GetMassData(&massData);
		massData.mass = CtypeValue<float32>::to(os, -params);
		self->SetMassData(&massData);
		return 0;
	}

	static int setInertia(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(b2Body*);
		b2MassData massData;
		self->GetMassData(&massData);
		massData.I = CtypeValue<float32>::to(os, -params);
		self->SetMassData(&massData);
		return 0;
	}

	static int setPosition(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(b2Body*);
		b2Transform xf = self->GetTransform();
		xf.p = CtypeValue<b2Vec2>::to(os, -params);
		self->SetTransform(xf.p, xf.q.GetAngle());
		return 0;
	}

	static int setAngle(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(b2Body*);
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
			shape->m_p = CtypeValue<b2Vec2>::to(os, -1);
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
		shape->m_vertex1 = CtypeValue<b2Vec2>::to(os, -1);
		os->pop();

		os->getProperty(offs, "vertex2", false); // optional
		if(os->isNull()) return error(shape, os, "vertex2 expected by edge shape");
		shape->m_vertex2 = CtypeValue<b2Vec2>::to(os, -1);
		os->pop();

		os->getProperty(offs, "vertex0", false); // optional
		if(!os->isNull()){
			shape->m_vertex0 = CtypeValue<b2Vec2>::to(os, -1);
			shape->m_hasVertex0 = true;
		}
		os->pop();

		os->getProperty(offs, "vertex3", false); // optional
		if(!os->isNull()){
			shape->m_vertex3 = CtypeValue<b2Vec2>::to(os, -1);
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
			vertices[i] = CtypeValue<b2Vec2>::to(os, -1);
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
			vertices[i] = CtypeValue<b2Vec2>::to(os, -1);
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
			vertices[i] = CtypeValue<b2Vec2>::to(os, -1);
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
		def.density = os->popFloat(1.0f); // def.density);

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
		}else if(os->isArray()){
			b2FixtureDef def;
			def.shape = toAutoPolygonShape(os, -1);
			if(!def.shape) return;
			os->pop();
			
			populateFixtureDef(def, os, offs);
			
			self->CreateFixture(&def);

			def.shape->~b2Shape();
			os->free((void*)def.shape);
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
				os->getProperty(offs, "radius", false); // optional
				if(!os->isNull()){
					b2FixtureDef def;
					def.shape = new (os->malloc(sizeof(b2CircleShape) OS_DBG_FILEPOS)) b2CircleShape();
					((b2CircleShape*)def.shape)->m_radius = toBox2dMetric(os->popFloat());
			
					populateFixtureDef(def, os, offs);
			
					self->CreateFixture(&def);

					def.shape->~b2Shape();
					os->free((void*)def.shape);
				}else{
					os->pop();
					b2Shape * shape = toShape(os, offs);
					if(!shape) return;
					float density = os->toFloat(offs+1, 1.0f);
					self->CreateFixture(shape, density);
					shape->~b2Shape();
					os->free(shape);
				}
			}
		}
	}

	static int createFixture(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(b2Body*);
		if(os->isObject(-params)){
			createFixture(self, os, -params);
			return 0;
		}
		os->triggerError(OS_E_ERROR, "error arguments");
		return 0;
	}

	static int getWorld(OS * os, int params, int, int, void*)
	{
		OS_GET_SELF(b2Body*);
		CtypeValue<World*>::push(os, World::toWorld(self->GetWorld()));
		return 1;
	}

	static void init(OS * os)
	{
		OS::FuncDef funcs[] = {
			{"createFixture", createFixture},
			// OS_GET_METHOD_1_NOT_CONST(b2Body, b2Fixture*, createFixture, CreateFixture, const b2FixtureDef*),
			// OS_GET_METHOD_2_NOT_CONST(b2Body, b2Fixture*, createFixtureByShape, CreateFixture, const b2Shape*, float32),
			OS_VOID_METHOD_1(b2Body, destroyFixture, DestroyFixture, b2Fixture*),
			OS_VOID_METHOD_2(b2Body, setTransform, SetTransform, const b2Vec2&, float32),
			OS_GET_METHOD(b2Body, const b2Transform&, transform, GetTransform),
			OS_GET_METHOD(b2Body, const b2Vec2&, position, GetPosition),
			{"__set@position", setPosition},
			OS_GET_METHOD(b2Body, float32, angle, GetAngle),
			{"__set@angle", setAngle},
			OS_GET_METHOD(b2Body, const b2Vec2&, worldCenter, GetWorldCenter),
			OS_GET_METHOD(b2Body, const b2Vec2&, localCenter, GetLocalCenter),
			OS_SET_METHOD(b2Body, const b2Vec2&, linearVelocity, SetLinearVelocity),
			OS_GET_METHOD(b2Body, b2Vec2, linearVelocity, GetLinearVelocity),
			OS_SET_METHOD(b2Body, float32, angularVelocity, SetAngularVelocity),
			OS_GET_METHOD(b2Body, float32, angularVelocity, GetAngularVelocity),
			OS_VOID_METHOD_2(b2Body, applyForce, ApplyForce, const b2Vec2&, const b2Vec2&),
			OS_VOID_METHOD_1(b2Body, applyForceToCenter, ApplyForceToCenter, const b2Vec2&),
			OS_VOID_METHOD_1(b2Body, applyTorque, ApplyTorque, float32),
			OS_VOID_METHOD_2(b2Body, applyLinearImpulse, ApplyLinearImpulse, const b2Vec2&, const b2Vec2&),
			OS_VOID_METHOD_1(b2Body, applyAngularImpulse, ApplyAngularImpulse, float32),
			OS_GET_METHOD(b2Body, float32, mass, GetMass),
			{"__set@mass", setMass},
			OS_GET_METHOD(b2Body, float32, inertia, GetInertia),
			{"__set@inertia", setInertia},
			{"__get@massCenter", getMassCenter},
			{"__set@massCenter", setMassCenter},
			// {"__get@massData", getMassData},
			// OS_SET_METHOD(b2Body, const b2MassData*, massData, SetMassData),
			OS_VOID_METHOD(b2Body, resetMassData, ResetMassData),
			OS_GET_METHOD_1(b2Body, b2Vec2, getWorldPoint, GetWorldPoint, const b2Vec2&),
			OS_GET_METHOD_1(b2Body, b2Vec2, getWorldVector, GetWorldVector, const b2Vec2&),
			OS_GET_METHOD_1(b2Body, b2Vec2, getLocalPoint, GetLocalPoint, const b2Vec2&),
			OS_GET_METHOD_1(b2Body, b2Vec2, getLocalVector, GetLocalVector, const b2Vec2&),
			OS_GET_METHOD_1(b2Body, b2Vec2, getLinearVelocityFromWorldPoint, GetLinearVelocityFromWorldPoint, const b2Vec2&),
			OS_GET_METHOD_1(b2Body, b2Vec2, getLinearVelocityFromLocalPoint, GetLinearVelocityFromLocalPoint, const b2Vec2&),
			OS_GET_METHOD_1(b2Body, b2Vec2, getLocalPoint, GetLocalPoint, const b2Vec2&),
			OS_GET_METHOD(b2Body, float32, linearDamping, GetLinearDamping),
			OS_SET_METHOD(b2Body, float32, linearDamping, SetLinearDamping),
			OS_GET_METHOD(b2Body, float32, angularDamping, GetAngularDamping),
			OS_SET_METHOD(b2Body, float32, angularDamping, SetAngularDamping),
			OS_GET_METHOD(b2Body, float32, gravityScale, GetGravityScale),
			OS_SET_METHOD(b2Body, float32, gravityScale, SetGravityScale),
			OS_GET_METHOD(b2Body, b2BodyType, type, GetType),
			OS_SET_METHOD(b2Body, b2BodyType, type, SetType),
			OS_SET_METHOD(b2Body, bool, isBullet, SetBullet),
			OS_GET_METHOD(b2Body, bool, isBullet, IsBullet),
			OS_SET_METHOD(b2Body, bool, isSleepingAllowed, SetSleepingAllowed),
			OS_GET_METHOD(b2Body, bool, isSleepingAllowed, IsSleepingAllowed),
			OS_SET_METHOD(b2Body, bool, isAwake, SetAwake),
			OS_GET_METHOD(b2Body, bool, isAwake, IsAwake),
			OS_SET_METHOD(b2Body, bool, isActive, SetActive),
			OS_GET_METHOD(b2Body, bool, isActive, IsActive),
			OS_SET_METHOD(b2Body, bool, isFixedRotation, SetFixedRotation),
			OS_GET_METHOD(b2Body, bool, isFixedRotation, IsFixedRotation),
			OS_GET_METHOD(b2Body, const b2Fixture*, fixtureList, GetFixtureList),
			// OS_GET_METHOD(b2Body, const b2JointEdge*, jointList, GetJointList),
			// OS_GET_METHOD(b2Body, const b2ContactEdge*, contactList, GetContactList),
			OS_GET_METHOD(b2Body, const b2Body*, next, GetNext),
			// OS_GET_METHOD(b2Body, const b2World*, world, GetWorld),
			{"__get@world", getWorld},
			{}
		};

		createCtypePrototype<b2Body>(os, funcs);
	}
};

void World::createBodyFixture(b2Body * body, OS * os, int offs)
{
	Body::createFixture(body, os, offs);
}

}; // namespace ObjectScript

using namespace ObjectScript;

void initBox2d(OS * os)
{
	World::init(os);
	Body::init(os);
}

