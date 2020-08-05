#include<AdvancedPhysics/collide_fine_advanced.h>


namespace rtcdNS {


	// region R = { (x, y, z) | min.x<=x<=max.x, min.y<=y<=max.y, min.z<=z<=max.z }
	struct AABB {
		Point min;
		Point max;
	};


	// Region R = { x | (x - [a + (b - a)*t])?2 <= r }, 0 <= t <= 1
	struct Capsule {
		Point a; // Medial line segment start point
		Point b; // Medial line segment endpoint
		float r; // Radius
	};

	// Region R = { x | (x - [a + u[0]*s + u[1]*t])?2 <= r }, 0 <= s,t <= 1
	struct Lozenge {
		Point a; // Origin
		Vector3 u[2]; // The two edges axes of the rectangle
		float r; // Radius
	};

	struct Segment {


	};


	//////////ORIGINALE

	//unsigned AdvancedCollisionDetector::BoxAndSphere(
	//	const CollisionBox &box,
	//	const CollisionSphere &sphere,
	//	CollisionData *data
	//)
	//{
	//	
	//	Vector3 centre = sphere.getAxis(3);
	//	Vector3 relCentre = box.getTransform().transformInverse(centre);

	//	// Early out check to see if we can exclude the contact
	//	if (real_abs(relCentre.x) - sphere.radius > box.halfSize.x ||
	//		real_abs(relCentre.y) - sphere.radius > box.halfSize.y ||
	//		real_abs(relCentre.z) - sphere.radius > box.halfSize.z)
	//	{
	//		return 0;
	//	}

	//	Vector3 closestPt(0, 0, 0);
	//	real dist;

	//	// Clamp each coordinate to the box.
	//	dist = relCentre.x;
	//	if (dist > box.halfSize.x) dist = box.halfSize.x;
	//	if (dist < -box.halfSize.x) dist = -box.halfSize.x;
	//	closestPt.x = dist;

	//	dist = relCentre.y;
	//	if (dist > box.halfSize.y) dist = box.halfSize.y;
	//	if (dist < -box.halfSize.y) dist = -box.halfSize.y;
	//	closestPt.y = dist;

	//	dist = relCentre.z;
	//	if (dist > box.halfSize.z) dist = box.halfSize.z;
	//	if (dist < -box.halfSize.z) dist = -box.halfSize.z;
	//	closestPt.z = dist;

	//	// Check we're in contact
	//	dist = (closestPt - relCentre).squareMagnitude();
	//	if (dist > sphere.radius * sphere.radius) return 0;

	//	// Compile the contact
	//	Vector3 closestPtWorld = box.getTransform().transform(closestPt);

	//	Contact* contact = data->contacts;
	//	contact->contactNormal = (closestPtWorld - centre);
	//	contact->contactNormal.normalise();
	//	contact->contactPoint = closestPtWorld;
	//	contact->penetration = sphere.radius - real_sqrt(dist);
	//	contact->setBodyData(box.body, sphere.body,
	//		data->friction, data->restitution);

	//	data->addContacts(1);
	//	return 1;

	//
	//}


	////////////////////////////////////////////DA QUI


	unsigned AdvancedCollisionDetector::BoxAndSphere(
		const CollisionBox &box,
		const CollisionSphere &sphere,
		CollisionData *data
	)
	{

		// Compute the AABB resulting from expanding b by sphere radius r
		//AABB e = b;
		//e.min.x -= s.radius; e.min.y -= s.radius; e.min.z -= s.radius;
		//e.max.x += s.radius; e.max.y += s.radius; e.max.z += s.radius;
		//// Intersect ray against expanded AABB e. Exit with no intersection if ray
		//// misses e, else get intersection point p and time t as result
		//Vector3 p;
		//if (!IntersectRayAABB(s.getAxis(3), sphereRelmov, e, t, p) || t > 1.0f)
		//	return 0;
		//else
		//{
		//	/* se sono qui so che ho l'intersezione del raggio con il box in cui ogni lato è stato
		//aumentato del raggio della sfera (bisogna rimuovere però gli spigoli!)*/
		//	Contact* contact = data->contacts;
		//	contact->contactNormal = (closestPtWorld - centre);
		//	contact->contactNormal.normalise();
		//	contact->contactPoint = closestPtWorld;
		//	contact->penetration = sphere.radius - real_sqrt(dist);
		//	contact->setBodyData(box.body, sphere.body,
		//		data->friction, data->restitution);

		//	data->addContacts(1);
			return 1;


		//}



		

		
	}


	//AABB pag 78-79
	//pag 229 ericson
	//d is the movement of the sphere
	int IntersectMovingSphereAABB(CollisionSphere s, Vector3 sphereRelmov, AABB b, float &t)
	{
		// Compute the AABB resulting from expanding b by sphere radius r
	//	AABB e = b;
	//	e.min.x -= s.radius; e.min.y -= s.radius; e.min.z -= s.radius;
	//	e.max.x += s.radius; e.max.y += s.radius; e.max.z += s.radius;
	//	// Intersect ray against expanded AABB e. Exit with no intersection if ray
	//	// misses e, else get intersection point p and time t as result
	//	Vector3 p;
	//	if (!IntersectRayAABB(s.getAxis(3), sphereRelmov, e, t, p) || t > 1.0f)
	//		return 0;
	//	else
	//	{
	//		/* se sono qui so che ho l'intersezione del raggio con il box in cui ogni lato è stato
	//	aumentato del raggio della sfera (bisogna rimuovere però gli spigoli!)*/



	//	}


	//	// Compute which min and max faces of b the intersection point p lies
	//	// outside of. Note, u and v cannot have the same bits set and
	//	// they must have at least one bit set among them
	//	int u = 0, v = 0;

	//	/* |= Assignment by bitwise OR, es : 10110110 | 01101100 = 11111110 (mette 1 dove trova 1 su uno o l'altro numero),
	//	in questo modo è come se facessi u += 1; u += 2; u+=4;*/
	//	if (p.x < b.min.x) u |= 1;/*0001*/
	//	if (p.x > b.max.x) v |= 1;
	//	if (p.y < b.min.y) u |= 2;/*0010*/
	//	if (p.y > b.max.y) v |= 2;
	//	if (p.z < b.min.z) u |= 4;/*0100*/
	//	if (p.z > b.max.z) v |= 4;
	//	// ‘Or’ all set bits together into a bit mask (note: here u + v == u | v)
	//	int m = u + v;
	//	// Define line segment [c, c+d] specified by the sphere movement
	//	Segment seg(s.c, s.c + d);

	//	// If all 3 bits set (m == 7) then p is in a vertex region
	//	/*infatti ad esempio avremmo : p.x < b.min.x, p.y < b.min.y , p.z < b.min. z => u */
	//	if (m == 7) {
	//		// Must now intersect segment [c, c+d] against the capsules of the three
	//		// edges meeting at the vertex and return the best time, if one or more hit
	//			/*  ^ : XOR :restituisce true solo se gli input sono diversi
	//	es  2^4 = 0010 ^ 0100 = 0110 */
	//		float tmin = FLT_MAX;

	//		if (IntersectSegmentCapsule(seg, Corner(b, v), Corner(b, v ^ 1), s.radius, &t))
	//			tmin = Min(t, tmin);
	//		if (IntersectSegmentCapsule(seg, Corner(b, v), Corner(b, v ^ 2), s.radius, &t))
	//			tmin = Min(t, tmin);
	//		if (IntersectSegmentCapsule(seg, Corner(b, v), Corner(b, v ^ 4), s.radius, &t))
	//			tmin = Min(t, tmin);
	//		if (tmin == FLT_MAX) return 0; // No intersection
	//		t = tmin;
	//		return 1; // Intersection at time t == tmin
	//	}
	//	// If only one bit set in m, then p is in a face region

	//	/*& : bitwise operator : dati 10110101 & 01110110 = 001100100 eg mette 1 solo se sono entrambi 1*/
	//	/* (es m = 2 => p.y > b.min/max.y mentre p.x e p.z sono dentro b) */
	//	/*m - 1 = 0010 - 0001 = 0001 = 1*/
	//	/* m & (m-1) = 0010 & 0000 = 0000 = 0*/

	//	/*(es2 m = 7 => siamo su uno spigolo, verifichiamo che torni con quanto sopra)*/
	//	/* BITWISE AND OPERATOR*/
	//	/* m = 7 = 0111 = 0*2^3 + 1*2*2 + 1*2^1 + 1*2^0
	//	m - 1 = 6 = 0110
	//	m & m -1 = 0111 & 0110 = 0110 != 0  => con m = 7  non entriamo...corretto !!*/
	//	if ((m & (m - 1)) == 0) {
	//		// Do nothing. Time t from intersection with
	//		// expanded box is correct intersection time
	//		return 1;
	//	}
	//	// p is in an edge region. Intersect against the capsule at the edge

	//	return IntersectSegmentCapsule(seg, Corner(b, u ^ 7), Corner(b, v), s.r, &t);
	
	
		return 1;
	}



	// Intersect ray R(t) = p + t*d against AABB a. When intersecting,
// return intersection distance tmin and point q of intersection
	//p è la posizione della sfera
	//d è il movimento della sfera
	int IntersectRayAABB(Vector3 spherecenter, Vector3 sphererelmov, AABB a, float &tmin, Vector3 &q)
	{
		//tmin = 0.0f; // set to -FLT_MAX to get first hit on line
		//float tmax = FLT_MAX; // set to max distance ray can travel (for segment)
		//static constexpr float EPSILON = 0.000001;
		//
		///*valutiamo se c'è moto relativo -componente per componente - tra sfera e box 
		//se è molto piccolo verifichiamo che la posizione
		//corrente della sfera sia tale da permettere collisione col box.
		//se anche questa condizione non è verificata => non ci può essere collisione => return 0*/
		//for (int i = 0; i < 3; i++) {
		//	if (std::fabs(sphererelmov[i]) < EPSILON) {
		//		
		//		if (spherecenter[i] < a.min[i] || spherecenter[i] > a.max[i]) return 0;/*nessuna collisione*/
		//	}
		//	else {
		//		/*arrivato qui sò soltanto che c'è moto relativo (sulla componente i-esima) tra sfera e box
		//		ma non so ancora se il moto è di avvicinamento o di allontanamento e quindi
		//		non so se ci sarà collisione*/

		//		// Compute intersection t value of ray with near and far plane of slab
		//		//ood da vedere come l'inverso della velocità lungo la componente i
		//		float ood = 1.0f / sphererelmov[i];

		//		/*tempo = distanza/velocità*/
		//		/*tempo necessario affinchè la componente i-esima del centro della sfera
		//		eguagli la rispettiva componente del vertice minimo del bounding box*/
		//		float t1 = (a.min[i] - spherecenter[i]) * ood;
		//		/*tempo necessario affinchè la componente i-esima del centro della sfera
		//		eguagli la rispettiva componente del vertice massimo del bounding box*/
		//		float t2 = (a.max[i] - spherecenter[i]) * ood;
		//		// Make t1 be intersection with near plane, t2 with far plane
		//		/*(in generale non sappiamo se (lungo la componente i-esima) 
		//		ci avviciniamo "da sopra" o "da sotto"*/
		//		if (t1 > t2) swap(t1, t2);
		//		// Compute the intersection of slab intersection intervals
		//		if (t1 > tmin) tmin = t1;
		//		if (t2 > tmax) tmax = t2;

		//		// Exit with no collision as soon as slab intersection becomes empty
		//		/*se tmin > tmax, significa che la componente i-esima del raggio
		//		non raggiunge mai la rispettiva componente nè del vertice max nè del vertice minimo del bounding box
		//		pertanto non c'è intersezione (basta una sola componente per determinare la NON intersezione)  */
		//		if (tmin > tmax) return 0;
		//	}
		//}
		//// Ray intersects all 3 slabs. Return point (q) and intersection t value (tmin)
		///*q = centro iniziale della sfera + velocità sfera per tempo_collisione*/
		//q = spherecenter + sphererelmov * tmin;
		return 1;
	}

	
	// Support function that returns the AABB vertex with index n
	Point Corner(AABB b, int n)
	{
		Point p;
		p.x = ((n & 1) ? b.max.x : b.min.x); 
		p.y = ((n & 1) ? b.max.y : b.min.y);
		p.z = ((n & 1) ? b.max.z : b.min.z);
		return p;
	}


	int TestSphereCapsule(CollisionSphere s, Capsule capsule)
	{
		//// Compute (squared) distance between sphere center and capsule line segment
		//float dist2 = SqDistPointSegment(capsule.a, capsule.b, s.c);
		//// If (squared) distance smaller than (squared) sum of radii, they collide
		//float radius = s.r + capsule.r;
		//return dist2 <= radius * radius;
		return 1;
	}
	int TestCapsuleCapsule(Capsule capsule1, Capsule capsule2)
	{
		// Compute (squared) distance between the inner structures of the capsules
		//float s, t;
		//Point c1, c2;
		//float dist2 = ClosestPtSegmentSegment(capsule1.a, capsule1.b,
		//	capsule2.a, capsule2.b, s, t, c1, c2);
		//// If (squared) distance smaller than (squared) sum of radii, they collide
		//float radius = capsule1.r + capsule2.r;
		//return dist2 <= radius * radius;

		return 1;
	}



	void swap(float& t1, float& t2)
	{
		const float t3 = t1;
		t1 = t2;
		t2 = t3;
	}

}