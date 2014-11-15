pinocchio-importer
==================

Imports the skeleton and attachment files produced by [Pinocchio](http://www.mit.edu/~ibaran/autorig/pinocchio.html).

This library provides easy access to joint data such as their parent, children, world location, and distance to parent joint.

## Usage
Ensure that load() is called before accessing the members.

```
PinocchioImporter pi;
pi.load("skeleton.out", "attachment.out");
```

## Members
```
struct joint {
    int id, parent;
    float x, y, z, distanceToParent;
    vector<int> children;
};

vector<joint> joints;
vector<vector<float>> attachments;
size_t numJoints;
size_t numVertices;
```

### Notes
The distanceToParent value is Euclidean distance.

You can access the parent joint by using the id as the index of the vector. For example:

```  
joint child = joints[1];  
joint parent = joints[child.parent];  
```