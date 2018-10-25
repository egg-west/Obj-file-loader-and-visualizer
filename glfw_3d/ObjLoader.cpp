#include "ObjLoader.h"

using namespace std;
bool ObjLoader::load(const string fp) {
	fstream objFs;
	stringstream ss;
	string line;
	vector<GLfloat> vv(3, 0);
	vector<GLint> fv(3, 0);
	objFs.open(fp, ios::in);
	if (!objFs.is_open()) {
		std::cerr << "the file does not exist." << std::endl;

		return false;
	}

	while (!objFs.eof()) {
		getline(objFs, line);
		
		if (line[0] != 'v' && line[0] != 'f') continue;
		
		
		if (line[0] == 'v' && line[1] == ' ') {
			line.erase(line.begin(), line.begin() + 1);
			ss.clear(); ss.str(line);
			ss >> vv[0] >> vv[1] >> vv[2];
			V.push_back(vv);
		}
		else if (line[0] == 'f' && line[1] == ' ') {
			line.erase(line.begin(), line.begin() + 1);
			ss.clear(); ss.str(line);
			ss >> fv[0] >> fv[1] >> fv[2];
			F.push_back(fv);
		}
	}
	objFs.close();
	//std::cout << "sizeof V: " << V.size() << "  sizeof F:" << F.size() << endl;
	//std::cout << V[0][0] <<" "<< V[0][1] << " " << V[0][2] << " "  << endl;
	//std::cout << F[0][0] << " " << F[0][1] << " " << F[0][2] << " " << endl;
	return true;
}

bool ObjLoader::draw() {
	glBegin(GL_TRIANGLES);

	for (int i = 0; i<F.size(); i++) {
		glm::vec3 NV(0.0f);

		
		glm::vec3 SV1(0.0f), SV2(0.0f), SV3(0.0f);
		if (F[i].size() == 3) {
			GLint idx1 = F[i][0]-1, idx2 =F[i][1]-1, idx3 = F[i][2]-1;
			if (idx1 > V.size() || idx2 >= V.size() || idx3 >= V.size()) {
				cout << "idx out of range: "<<idx1<<" "<<idx2<<" "<<idx3<< endl;
				getchar();
			}
			
			SV1 = { V[idx1][0], V[idx1][1],V[idx1][2] };
			SV2 = { V[idx2][0], V[idx2][1],V[idx2][2] };
			SV3 = { V[idx3][0], V[idx3][1],V[idx3][2] };
			
			// normalize vector
			NV = glm::fastNormalize(glm::cross(SV1 - SV2, SV1 - SV3));

			// set normal vector
			glNormal3f(NV[0], NV[1], NV[2]);

			glVertex3f(SV1[0], SV1[1], SV1[2]);
			glVertex3f(SV2[0], SV2[1], SV2[2]);
			glVertex3f(SV3[0], SV3[1], SV3[2]);
		}
		else {
			std::cout << "this v is not in size 3" << endl;
		}
	}

	glEnd();
	return true;

}