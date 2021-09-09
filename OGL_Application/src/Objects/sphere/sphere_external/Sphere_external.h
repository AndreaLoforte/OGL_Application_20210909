///////////////////////////////////////////////////////////////////////////////
// Sphere.h
// ========
// Sphere for OpenGL with (radius, sectors, stacks)
// The min number of sectors is 3 and The min number of stacks are 2.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2017-11-01
// UPDATED: 2020-05-20
///////////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_SPHERE_H
#define GEOMETRY_SPHERE_H
#include<shadersFacility/shaderobject.h>
#include<applicationDerivedObject.h>
#include <vector>

namespace myobjectNS {

    class Sphere2 : public myobjectNS::ShaderObject, public myobjectNS::ObjectSphere
    {
    public:
        // ctor/dtor
        Sphere2(std::string sh_prog_name, float radius = 1.0f, int sectorCount = 36, int stackCount = 18, bool smooth = true);
        ~Sphere2() {}

        // getters/setters
        float getRadius() const { return radius; }
        int getSectorCount() const { return sectorCount; }
        int getStackCount() const { return stackCount; }
        void set(float radius, int sectorCount, int stackCount, bool smooth = true);
        void setRadius(float radius);
        void setSectorCount(int sectorCount);
        void setStackCount(int stackCount);
        void setSmooth(bool smooth);

        // for vertex data
        unsigned int getVertexCount() const { return (unsigned int)vertices.size() / 3; }
        unsigned int getNormalCount() const { return (unsigned int)normals.size() / 3; }
        unsigned int getTexCoordCount() const { return (unsigned int)texCoords.size() / 2; }
        unsigned int getIndexCount() const { return (unsigned int)indices.size(); }
        unsigned int getLineIndexCount() const { return (unsigned int)lineIndices.size(); }
        unsigned int getTriangleCount() const { return getIndexCount() / 3; }
        unsigned int getVertexSize() const { return (unsigned int)vertices.size() * sizeof(float); }
        unsigned int getNormalSize() const { return (unsigned int)normals.size() * sizeof(float); }
        unsigned int getTexCoordSize() const { return (unsigned int)texCoords.size() * sizeof(float); }
        unsigned int getIndexSize() const { return (unsigned int)indices.size() * sizeof(unsigned int); }
        unsigned int getLineIndexSize() const { return (unsigned int)lineIndices.size() * sizeof(unsigned int); }
        const float* getVertices() const { return vertices.data(); }
        const float* getNormals() const { return normals.data(); }
        const float* getTexCoords() const { return texCoords.data(); }
        const unsigned int* getIndices() const { return indices.data(); }
        const unsigned int* getLineIndices() const { return lineIndices.data(); }

        // for interleaved vertices: V/N/T
        unsigned int getInterleavedVertexCount() const { return getVertexCount(); }    // # of vertices
        unsigned int getInterleavedVertexSize() const { return (unsigned int)interleavedVertices.size() * sizeof(float); }    // # of bytes
        int getInterleavedStride() const { return interleavedStride; }   // should be 32 bytes
        const float* getInterleavedVertices() const { return interleavedVertices.data(); }

        // draw in VertexArray mode
        void drawLines(const float lineColor[4]) const;     // draw lines only
        void drawWithLines(const float lineColor[4]) const; // draw surface and lines

        // debug
        void printSelf() const;

    protected:

    private:
        // member functions
        void buildVerticesSmooth();
        void buildVerticesFlat();
        void buildInterleavedVertices();
        void clearArrays();
        void addVertex(float x, float y, float z);
        void addNormal(float x, float y, float z);
        void addTexCoord(float s, float t);
        void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
        std::vector<float> computeFaceNormal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3);

        // memeber vars
        float radius;
        int sectorCount;                        // longitude, # of slices
        int stackCount;                         // latitude, # of stacks
        bool smooth;
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> texCoords;
        std::vector<unsigned int> indices;
        std::vector<unsigned int> lineIndices;

        // interleaved
        std::vector<float> interleavedVertices;
        int interleavedStride;                  // # of bytes to hop to the next vertex (should be 32 bytes)
        
                                                
        /********************/
        void clean() {}
        //void update(const float&) override;

        void create()override;
        void render(const fpcameraNS::Transformation&) override;
        //void render();
        //void setRigidBodyParameters();
      /*  void reset() override {
            setRigidBodyParameters();
        }*/
        //Sphere* getClassTypePointer()override { return this; }
        //void setParameters() override;
        Sphere2* getNewInstance() override {
            instanceCounter++;
            Sphere2* s(new Sphere2("sphere_external"));
            s->AOinstanceNumber = instanceCounter;
            return s;
        }




    };




}


#endif

