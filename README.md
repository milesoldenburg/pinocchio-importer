pinocchio-importer
==================

Imports the skeleton and attachment files produced by [Pinocchio](http://www.mit.edu/~ibaran/autorig/pinocchio.html).

## Usage
Ensure that load() is called before accessing the members.

```
PinocchioImporter pi;
pi.load("skeleton.out", "attachment.out");
```

## Members
```
struct joint {
    int id, previousId;
    float x, y, z;
};

vector<joint> joints;
vector<vector<float>> attachments;
size_t numJoints;
size_t numVertices;
```