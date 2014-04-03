#include "loader.hpp"


//IMPORTANT: assume the world consist of triangles or quads. flag 0 = triangle. flag 1 = quad.
int objFileLoader::load(std::string filename){
	std::ifstream in(filename.c_str());
	if(!in.is_open()){
		std::cout<<"load error:"<<filename<<std::endl;
		return -1;
	}
	std::string path=filename.substr(0,(filename.find_last_of('/')!=std::string::npos ? filename.find_last_of('/')+1 : 0));
	char buffer[256];//line buffers
	//read in each line into a vector.
	int counter=0;
	std::cout <<" loading "<<filename<<std::endl;
	while(!in.eof()){
		// std::cout<<counter<<std::endl;
		in.getline(buffer,256);
		lines.push_back(new std::string(buffer));//create a new string represent the line.
		counter++;
	}
	for (int i=0;i<lines.size();i++){
		 
		if((*lines[i])[0]=='#'){continue;}//if starting with #,header. dont' give a fuck.
		else if((*lines[i])[0]=='v'&&(*lines[i])[1]==' '){//if this line starting with v.
			float x,y,z;
			sscanf(lines[i]->c_str(),"v %f %f %f",&x,&y,&z);
			// std::cout<<"x y z is "<<x<<" "<<y<<" "<<z<<std::endl;
			vertices.push_back(new Vector3D(x,y,z));
		}
		else if((*lines[i])[0]=='v'&&(*lines[i])[1]=='n'){//if it's normals.
			float x,y,z;
			sscanf(lines[i]->c_str(),"vn %f %f %f",&x,&y,&z);
			normals.push_back(new Vector3D(x,y,z));
		}
		else if((*lines[i])[0]=='f'){

			int vectorIndex1,normalIndex;
			int vectorIndex2;
			int vectorIndex3;
			int vectorIndex4;
			if(count(lines[i]->begin(),lines[i]->end(),' ')==3){//triangle mesh.
			sscanf(lines[i]->c_str(),"f %d//%d %d//%d %d//%d",&vectorIndex1,&normalIndex,&vectorIndex2,&normalIndex,&vectorIndex3,&normalIndex);
			// std::cout<<"list is "<<vectorIndex1<<std::endl;
			faces.push_back(new face(vectorIndex1,vectorIndex2,vectorIndex3,normalIndex));
			flag = 0;
			}
			else if(count(lines[i]->begin(),lines[i]->end(),' ')==4){//quad mash.
				sscanf(lines[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&vectorIndex1,&normalIndex,&vectorIndex2,
																	&normalIndex,&vectorIndex3,&normalIndex,&vectorIndex4,&normalIndex);
				faces.push_back(new face(vectorIndex1,vectorIndex2,vectorIndex3,vectorIndex4,normalIndex));
				if (true){
					// std::cout<<(*normals[normalIndex-1])<<std::endl;
					// Plane* collisionPlane = Plane((*vertices[vectorIndex1-1]),(*vertices[vectorIndex2-1]),(*vertices[vectorIndex3-1]),
					// 							 (*vertices[vectorIndex4-1]),(*normals[normalIndex-1]));
					collplane.push_back(new Plane((*vertices[vectorIndex1-1]),(*vertices[vectorIndex2-1]),(*vertices[vectorIndex3-1]),
												 (*vertices[vectorIndex4-1]),(*normals[normalIndex-1])));
					// std::cout<<"[DEBUG]"<<vectorIndex4<<std::endl;
					flag = 1;
				}
				else{
					std::cout<<"NULL coll plane!"<<std::endl;
				}
			}
		}
	}
	// std::cout<<"list is "<<faces.size()<<std::endl;
}
void objFileLoader::draw(){
	callerIndex = glGenLists(1);
	glNewList(callerIndex,GL_COMPILE);
	// std::cout<<"list is "<<faces.size()<<std::endl;
		// std::cout<<"Drawing callerIndex "<<callerIndex<<std::endl;
	if(flag==0&&texture!=0){
	for (int i=0;i<faces.size();i++){
	// std::cout<<"drawing"<<std::endl;
	glBegin(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D,texture);
	glNormal3f((*normals[faces[i]->normal-1])[0],(*normals[faces[i]->normal-1])[1],(*normals[faces[i]->normal-1])[2]);
	glTexCoord2f(0,0);
	glVertex3f((*vertices[faces[i]->vertex1-1])[0],(*vertices[faces[i]->vertex1-1])[1],(*vertices[faces[i]->vertex1-1])[2]);
	glTexCoord2f(0.5,1);
	glVertex3f((*vertices[faces[i]->vertex2-1])[0],(*vertices[faces[i]->vertex2-1])[1],(*vertices[faces[i]->vertex2-1])[2]);
	glTexCoord2f(0,1);
	glVertex3f((*vertices[faces[i]->vertex3-1])[0],(*vertices[faces[i]->vertex3-1])[1],(*vertices[faces[i]->vertex3-1])[2]);
	glEnd();
	}
	}
	else if(flag==0){
	for (int i=0;i<faces.size();i++){
	// std::cout<<"drawing"<<std::endl;
	glBegin(GL_TRIANGLES);
	// std::cout<<"debug "<<(*vertices[faces[i]->vertex1-1])[0]<<std::endl;
	glNormal3f((*normals[faces[i]->normal-1])[0],(*normals[faces[i]->normal-1])[1],(*normals[faces[i]->normal-1])[2]);
	glVertex3f((*vertices[faces[i]->vertex1-1])[0],(*vertices[faces[i]->vertex1-1])[1],(*vertices[faces[i]->vertex1-1])[2]);
	glVertex3f((*vertices[faces[i]->vertex2-1])[0],(*vertices[faces[i]->vertex2-1])[1],(*vertices[faces[i]->vertex2-1])[2]);
	glVertex3f((*vertices[faces[i]->vertex3-1])[0],(*vertices[faces[i]->vertex3-1])[1],(*vertices[faces[i]->vertex3-1])[2]);
	glEnd();
	}
	}
	else if(flag == 1&&texture!=0){
	for (int i=0;i<faces.size();i++){
	// std::cout<<"drawing Rectangle"<<std::endl;
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D,texture);
	glNormal3f((*normals[faces[i]->normal-1])[0],(*normals[faces[i]->normal-1])[1],(*normals[faces[i]->normal-1])[2]);
		glTexCoord2f(1,1);
	glVertex3f((*vertices[faces[i]->vertex1-1])[0],(*vertices[faces[i]->vertex1-1])[1],(*vertices[faces[i]->vertex1-1])[2]);
		glTexCoord2f(0,1);
	glVertex3f((*vertices[faces[i]->vertex2-1])[0],(*vertices[faces[i]->vertex2-1])[1],(*vertices[faces[i]->vertex2-1])[2]);
		glTexCoord2f(0,0);
	glVertex3f((*vertices[faces[i]->vertex3-1])[0],(*vertices[faces[i]->vertex3-1])[1],(*vertices[faces[i]->vertex3-1])[2]);
		glTexCoord2f(1,0);
	glVertex3f((*vertices[faces[i]->vertex4-1])[0],(*vertices[faces[i]->vertex4-1])[1],(*vertices[faces[i]->vertex4-1])[2]);
	glEnd();
	}
	}
	else if(flag == 1){
	for (int i=0;i<faces.size();i++){
	// std::cout<<"drawing Rectangle"<<std::endl;
	glBegin(GL_QUADS);
	glNormal3f((*normals[faces[i]->normal-1])[0],(*normals[faces[i]->normal-1])[1],(*normals[faces[i]->normal-1])[2]);
	glVertex3f((*vertices[faces[i]->vertex1-1])[0],(*vertices[faces[i]->vertex1-1])[1],(*vertices[faces[i]->vertex1-1])[2]);
	glVertex3f((*vertices[faces[i]->vertex2-1])[0],(*vertices[faces[i]->vertex2-1])[1],(*vertices[faces[i]->vertex2-1])[2]);
	glVertex3f((*vertices[faces[i]->vertex3-1])[0],(*vertices[faces[i]->vertex3-1])[1],(*vertices[faces[i]->vertex3-1])[2]);
	glVertex3f((*vertices[faces[i]->vertex4-1])[0],(*vertices[faces[i]->vertex4-1])[1],(*vertices[faces[i]->vertex4-1])[2]);
	glEnd();
	}
}
	glEndList();
}

void objFileLoader::drawQuads(){
	for (int i=0;i<faces.size();i++){
	// std::cout<<"drawing"<<std::endl;
	if (i==faces.size()-7){
		glBindTexture(GL_TEXTURE_2D,roof);
	}
	else{
		glBindTexture(GL_TEXTURE_2D,texture);
	}
	glBegin(GL_QUADS);
	// std::cout<<"debug "<<(*vertices[faces[i]->vertex1-1])[0]<<std::endl;
	// glNormal3f((*normals[faces[i]->normal-1])[0],(*normals[faces[i]->normal-1])[1],(*normals[faces[i]->normal-1])[2]);
	glTexCoord2f(1,1);
	glVertex3f((*vertices[faces[i]->vertex1-1])[0],(*vertices[faces[i]->vertex1-1])[1],(*vertices[faces[i]->vertex1-1])[2]);
	glTexCoord2f(0,1);
	glVertex3f((*vertices[faces[i]->vertex2-1])[0],(*vertices[faces[i]->vertex2-1])[1],(*vertices[faces[i]->vertex2-1])[2]);
	glTexCoord2f(0,0);
	glVertex3f((*vertices[faces[i]->vertex3-1])[0],(*vertices[faces[i]->vertex3-1])[1],(*vertices[faces[i]->vertex3-1])[2]);
	glTexCoord2f(1,0);
	glVertex3f((*vertices[faces[i]->vertex4-1])[0],(*vertices[faces[i]->vertex4-1])[1],(*vertices[faces[i]->vertex4-1])[2]);
	glEnd();
	}
}




unsigned int loadTexture(const char* name)
{
	SDL_Surface* img=SDL_LoadBMP(name);
	SDL_PixelFormat form={NULL,32,4,0,0,0,0,8,8,8,8,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
//	std::cout << img->w << " " << img->h << std::endl;
	SDL_Surface* img2=SDL_ConvertSurface(img,&form,SDL_SWSURFACE);
	unsigned int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,img2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	return texture;
}


