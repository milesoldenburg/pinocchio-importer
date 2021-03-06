#ifndef __PinocchioImporter__PinocchioImporter__
#define __PinocchioImporter__PinocchioImporter__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

struct joint {
    int         id,
                parent;
    float       x,
                y,
                z,
                distanceToParent = 0.0f;
    vector<int> children;
};

class PinocchioImporter {
private:
    vector<float> &split(const string &s, char delim, vector<float> &elems);
    vector<float> split(const string &s, char delim);
    
public:
    vector<joint> joints;
    vector<vector<float>> attachments;
    size_t numJoints;
    size_t numVertices;

    void load(const char * skeletonFile, const char * attachmentFile);
};

vector<float> &PinocchioImporter::split(const string &s, char delim, vector<float> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        float element;
        sscanf(item.c_str(), "%f", &element);
        elems.push_back(element);
    }
    return elems;
}


vector<float> PinocchioImporter::split(const string &s, char delim) {
    vector<float> elems;
    split(s, delim, elems);
    return elems;
}

/**
 * Loads skeletal joint data from the passed in file to a vector of joints
 * After calling load you may use the vectors
 */
void PinocchioImporter::load(const char * inputSkeletonFile, const char * inputAttachmentFile) {
    // Init line
    string line;
    
    // Open skeleton file
    ifstream skeletonFile;
    skeletonFile.open(inputSkeletonFile);
    
    // If the skeleton file is actually open
    if (skeletonFile.is_open()) {
        // Parse line by line until EOF
        while (getline(skeletonFile, line)) {
            // Populate joint with data
            joint currentJoint;
            sscanf(line.c_str(), "%i %f %f %f %i", &currentJoint.id, &currentJoint.x, &currentJoint.y, &currentJoint.z, &currentJoint.parent);
            
            // Add joint to array
            joints.push_back(currentJoint);
            
            // Clear data from string
            line.clear();
        }
    }
    
    // Close skeleton file
    skeletonFile.close();
    
    // Iterate every joint to calculate distance and to populate each children vector
    for (vector<joint>::iterator it = joints.begin(); it != joints.end(); ++it) {
        // Only process non-root nodes
        if (it->parent != -1) {
            // Add current joint to list of parents children
            joints[it->parent].children.push_back(it->id);
            
            // Calculate distance to parent
            it->distanceToParent = sqrtf(powf(it->x - joints[it->parent].x, 2.0f) + powf(it->y - joints[it->parent].y, 2.0f) + powf(it->z - joints[it->parent].z, 2.0f));
        }
    }
    
    // Open attachment file
    ifstream attachmentFile;
    attachmentFile.open(inputAttachmentFile);
    
    // If the attachment file is actually open
    if (attachmentFile.is_open()) {
        // Parse line by line until EOF
        while (getline(attachmentFile, line)) {
            line.append(" ");
            attachments.push_back(PinocchioImporter::split(line, ' '));
        }
    }
    
    // Get # joints and vertices
    numJoints = joints.size();
    numVertices = attachments.size();
}

#endif /* defined(__PinocchioImporter__PinocchioImporter__) */
