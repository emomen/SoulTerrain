//Author: Alonso Cardenas Sillas
//
//This c++ file is a reflection of my skills
//

void rocket(){
	for (int i=0; i<g.nbullets; i++) {
		Bullet *b = &g.barr[i];
		//Log("draw bullet...\n");
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POINTS);
		glVertex2f(b->pos[0],      b->pos[1]);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]);
		glVertex2f(b->pos[0],      b->pos[1]-1.0f);
		glVertex2f(b->pos[0],      b->pos[1]+1.0f);
		glColor3f(0.8, 0.8, 0.8);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
		glEnd();
	}

	//Left button is down
	//a little time between each bullet
	struct timespec bt;
	clock_gettime(CLOCK_REALTIME, &bt);
	double ts = timeDiff(&g.bulletTimer, &bt);
	if (ts > 0.1) {
		timeCopy(&g.bulletTimer, &bt);
		//shoot a bullet...
		if (g.nbullets < MAX_BULLETS) {
			Bullet *b = &g.barr[g.nbullets];
			timeCopy(&b->time, &bt);
			b->pos[0] = g.ship.pos[0];
			b->pos[1] = g.ship.pos[1];
			b->vel[0] = g.ship.vel[0];
			b->vel[1] = g.ship.vel[1];
			//convert ship angle to radians
			Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
			//convert angle to a vector
			Flt xdir = cos(rad);
			Flt ydir = sin(rad);
			b->pos[0] += xdir*20.0f;
			b->pos[1] += ydir*20.0f;
			b->vel[0] += xdir*6.0f + rnd()*0.1;
			b->vel[1] += ydir*6.0f + rnd()*0.1;
			b->color[0] = 1.0f;
			b->color[1] = 1.0f;
			b->color[2] = 1.0f;
			++g.nbullets;
		}
	}
}

