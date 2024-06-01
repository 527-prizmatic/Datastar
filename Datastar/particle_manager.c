#include "particle_manager.h"

#define LT_RD_F .4f /// Lifetime randomization factor

sfVertexArray* ptc_va;

void ptc_Init() {
	ptc_SSentinel = malloc(sizeof(PtcSystem));
	if (ptc_SSentinel == NULL) {
		log_LogStr(LOG_FATAL, "Particle engine initialization error - insufficient memory", sfTrue, sfTrue);
		return;
	}

	memset(ptc_SSentinel, 0, sizeof(PtcSystem));
	ptc_SSentinel->prev = NULL;
	ptc_SSentinel->next = NULL;
	ptc_SSentinel->type = PTC_SENTINEL;
	ptc_SSentinel->shape = PTCS_SENTINEL;

	ptc_PSentinel = malloc(sizeof(PtcParticle));
	if (ptc_PSentinel == NULL) {
		log_LogStr(LOG_FATAL, "Particle engine initialization error - insufficient memory", sfTrue, sfTrue);
		return;
	}

	memset(ptc_PSentinel, 0, sizeof(PtcParticle));
	ptc_PSentinel->prev = NULL;
	ptc_PSentinel->next = NULL;
	ptc_PSentinel->type = PTC_SENTINEL;
	ptc_va = sfVertexArray_create();
	if (ptc_va == NULL) {
		log_LogStr(LOG_FATAL, "Particle engine initialization error - insufficient memory", sfTrue, sfTrue);
		return;
	}
	sfVertexArray_setPrimitiveType(ptc_va, sfLineStrip);

	log_LogStr(LOG_INFO, "Particle engine initialization complete", sfTrue, sfTrue);
}

PtcSystem* ptc_CreateSystem(float _lts, float _ltp, int _pps, float _fmin, float _fmax, float _rmin, float _rmax, float _grav, sfRenderStates* _rs) {
	PtcSystem* sys = malloc(sizeof(PtcSystem));
	if (sys == NULL) {
		log_LogStr(LOG_ERROR, "Particle system creation error - insufficient memory", sfTrue, sfTrue);
		return NULL;
	}
	memset(sys, 0, sizeof(PtcSystem));
	sys->system_lifetime = _lts;
	sys->lifetime = _ltp;
	sys->pps = _pps;
	sys->force_min = _fmin;
	sys->force_max = _fmax;
	sys->dir_min = _rmin;
	sys->dir_max = _rmax;
	sys->gravity = _grav;
	sys->rState = _rs;
	sys->spawn_timer = 0.f;

	PtcSystem* n = ptc_SSentinel->next;
	ptc_SSentinel->next = sys;
	sys->prev = ptc_SSentinel;
	sys->next = n;
	if (n != NULL) n->prev = sys;

	return sys;
}

void ptc_SetType(PtcSystem* _ptcs, PtcType _type, ...) {
	if (_type == PTC_SENTINEL) {
		log_LogStr(LOG_ERROR, "Particle system type setup error - attempted to create particle system as reserved type PTC_SENTINEL", sfTrue, sfTrue);
		return;
	}

	_ptcs->type = _type;

	va_list args;
	va_start(args, _type);
	if (_type == PTC_CIRCLE) {
		_ptcs->size_min = va_arg(args, double);
		_ptcs->size_max = va_arg(args, double);
		_ptcs->clr1 = va_arg(args, sfColor);
		_ptcs->clr2 = va_arg(args, sfColor);
	}
	else if (_type == PTC_SPRITE) {
		_ptcs->id = va_arg(args, char*);
		_ptcs->scale_min = va_arg(args, double);
		_ptcs->scale_max = va_arg(args, double);
		_ptcs->rot_spd_min = va_arg(args, double);
		_ptcs->rot_spd_max = va_arg(args, double);
	}
	else if (_type == PTC_SHARD) {
		_ptcs->rds_min = va_arg(args, double);
		_ptcs->rds_max = va_arg(args, double);
		_ptcs->v_min = va_arg(args, int);
		_ptcs->v_max = va_arg(args, int);
		_ptcs->vclr1 = va_arg(args, sfColor);
		_ptcs->vclr2 = va_arg(args, sfColor);
	}
	else if (_type == PTC_BLAST) {
		_ptcs->rds_blast = va_arg(args, double);
		_ptcs->vertices = va_arg(args, int);
		_ptcs->blast_clr = va_arg(args, sfColor);
	}
//	printf("%s\n", _ptcs->id);
}

void ptc_SetShape(PtcSystem* _ptcs, PtcSShape _shape, ...) {
	if (_shape == PTCS_SENTINEL) {
		log_LogStr(LOG_ERROR, "Particle system shape setup error - attempted to create particle system as reserved type PTCS_SENTINEL", sfTrue, sfTrue);
		return;
	}

	_ptcs->shape = _shape;

	va_list args;
	va_start(args, _shape);
	if (_shape == PTCS_POINT) {
		_ptcs->pos = va_arg(args, sfVector2f);
		_ptcs->rds = 0.f;
	}
	else if (_shape == PTCS_CIRCLE) {
		_ptcs->pos = va_arg(args, sfVector2f);
		_ptcs->rds = va_arg(args, double);
	}
	else {
		_ptcs->pos1 = va_arg(args, sfVector2f);
		_ptcs->pos2 = va_arg(args, sfVector2f);
	}
}

void ptc_CreateParticle(PtcType _type, sfVector2f _pos, sfVector2f _spd, float _lt, float _grav, sfRenderStates* _rs, ...) {
	if (_type == PTC_SENTINEL) {
		log_LogStr(LOG_ERROR, "Particle creation error - attempted to create particle out of system created as reserved type PTC_SENTINEL", sfTrue, sfTrue);
		return;
	}

	PtcParticle* ptc = malloc(sizeof(PtcParticle));
	if (ptc == NULL) {
		log_LogStr(LOG_ERROR, "Particle creation error - insufficient memory", sfTrue, sfTrue);
		return;
	}

	memset(ptc, 0, sizeof(PtcParticle));
	ptc->type = _type;
	ptc->pos = _pos;
	ptc->spd = _spd;
	ptc->lifetime = _lt;
	ptc->gravity = _grav;
	ptc->rState = _rs;

	/// Slight randomization of particle lifetime (+/- <20%)
	if (ptc->type != PTC_BLAST) {
		float lt_rd = _lt * LT_RD_F;
		ptc->lifetime -= lt_rd;
		ptc->lifetime += RANDF(0.f, (lt_rd * 2.f));
	}
	ptc->lifetime_max = ptc->lifetime;

	va_list args;
	va_start(args, _rs);
	if (_type == PTC_CIRCLE) {
		ptc->rds = va_arg(args, double);
		ptc->clr = va_arg(args, sfColor);
		ptc->origin = Vector2f(ptc->rds, ptc->rds);
	}
	else if (_type == PTC_SPRITE) {
		ptc->id = va_arg(args, char*);
		ptc->scale = va_arg(args, double);
		ptc->rot_spd = va_arg(args, double);
		sfVector2u texDims = sfTexture_getSize(tex_Fetch(ptc->id));
		ptc->origin = v_Mul(Vector2f((float)texDims.x, (float)texDims.y), .5f);
		ptc->rot = RANDF(0.f, 360.f);
	}
	else if (_type == PTC_SHARD) {
		ptc->v_rds = va_arg(args, double);
		ptc->v_count = va_arg(args, int);
		ptc->v_clr = va_arg(args, sfColor);
		ptc->v_rot = RANDF(0.f, 360.f);
		ptc->v_rot_spd = RANDF(-720.f, 720.f);
	}
	else if (_type == PTC_BLAST) {
		ptc->rds_blast = va_arg(args, double);
		ptc->vertices = va_arg(args, int);
		ptc->blast_clr = va_arg(args, sfColor);
	}

	PtcParticle* n = ptc_PSentinel->next;
	ptc_PSentinel->next = ptc;
	ptc->prev = ptc_PSentinel;
	ptc->next = n;
	if (n != NULL) n->prev = ptc;
}

void ptc_Update() {
	PtcSystem* itrS = ptc_SSentinel->next;
	while (itrS != NULL) {
		if (!FEQS(itrS->system_lifetime, -1.f)) itrS->spawn_timer += (float)itrS->pps * getDeltaTime();
		else itrS->spawn_timer += itrS->pps;

		while (itrS->spawn_timer >= 1.f) {
			sfVector2f posRand = NULLVECTF;
			if (itrS->shape == PTCS_CIRCLE) {
				float magRand = RANDF(0.f, itrS->rds);
				float angRand = RANDF(0.f, 6.28f);
				posRand = v_Add(itrS->pos, POL2REC(Vector2f(magRand, angRand)));
			}
			else if (itrS->shape == PTCS_RECTANGLE) {
				posRand.x = itp_Float(itrS->pos1.x, itrS->pos2.x, rand_unit(3), itp_Linear);
				posRand.y = itp_Float(itrS->pos1.y, itrS->pos2.y, rand_unit(3), itp_Linear);
			}
			else if (itrS->shape == PTCS_LINE) {
				float t = rand_unit(3);
				posRand.x = itp_Float(itrS->pos1.x, itrS->pos2.x, t, itp_Linear);
				posRand.y = itp_Float(itrS->pos1.y, itrS->pos2.y, t, itp_Linear);
			}
			else posRand = itrS->pos;

			float ForceRand = RANDF(itrS->force_min, itrS->force_max);
			float dirAngRand = RANDF(450.f - itrS->dir_max, 450.f - itrS->dir_min);
			dirAngRand = D2R(dirAngRand);
			sfVector2f dirRand = POL2REC(Vector2f(ForceRand, -dirAngRand));

			if (itrS->type == PTC_CIRCLE) {
				float rdsRand = RANDF(itrS->size_min, itrS->size_max);
				sfColor clrRand = ptc_RandomColor(itrS->clr1, itrS->clr2);

				ptc_CreateParticle(PTC_CIRCLE, posRand, dirRand, itrS->lifetime, itrS->gravity, NULL, rdsRand, clrRand);
			}
			else if (itrS->type == PTC_SPRITE) {
				float scaleRand = RANDF(itrS->scale_min, itrS->scale_max);
				float rotRand = RANDF(itrS->rot_spd_min, itrS->rot_spd_max);

				ptc_CreateParticle(PTC_SPRITE, posRand, dirRand, itrS->lifetime, itrS->gravity, NULL, itrS->id, scaleRand, rotRand);
			}
			else if (itrS->type == PTC_SHARD) {
				float rdsRand = RANDF(itrS->rds_min, itrS->rds_max);
				int vRand = RAND(itrS->v_min, itrS->v_max);
				sfColor clrRand = ptc_RandomColor(itrS->vclr1, itrS->vclr2);

				ptc_CreateParticle(PTC_SHARD, posRand, dirRand, itrS->lifetime, itrS->gravity, NULL, rdsRand, vRand, clrRand);
			}
			else if (itrS->type == PTC_BLAST) {
				ptc_CreateParticle(PTC_SHARD, posRand, dirRand, itrS->lifetime, itrS->gravity, NULL, itrS->rds_blast, itrS->vertices, itrS->blast_clr);
			}

			itrS->spawn_timer -= 1.f;
		}

		itrS->system_lifetime -= getDeltaTime();
		if (itrS->system_lifetime <= 0.f) itrS = ptc_DestroySystem(itrS);
		else itrS = itrS->next;
	}

	PtcParticle* itrP = ptc_PSentinel->next;
	while (itrP != NULL) {
		itrP->pos = v_Add(itrP->pos, itrP->spd);
		if (itrP->type == PTC_CIRCLE) itrP->clr.a = min(255, itrP->lifetime * (512.f / itrP->lifetime_max));
		else if (itrP->type == PTC_SPRITE) {
			itrP->clr_spr = ColorA(255, 255, 255, (int)(min(255, itrP->lifetime * (1024.f / itrP->lifetime_max))));
			itrP->rot += itrP->rot_spd * getDeltaTime();
		}
		else if (itrP->type == PTC_SHARD) {
			itrP->rot += itrP->rot_spd * getDeltaTime();
			itrP->clr.a = min(255, itrP->lifetime * (512.f / itrP->lifetime_max));
		}
		itrP->spd.y += itrP->gravity * getDeltaTime();
		itrP->spd = v_Mul(itrP->spd, pow(.1f, getDeltaTime()));

		itrP->lifetime -= getDeltaTime();
		if (itrP->lifetime <= 0.f) itrP = ptc_DestroyParticle(itrP);
		else itrP = itrP->next;
	}
}

void ptc_Render() {
	PtcParticle* itrP = ptc_PSentinel->next;
	while (itrP != NULL) {
		if (itrP->type == PTC_CIRCLE) rq_Draw(RQ_CIRCLE, itrP->rState, itrP->pos, itrP->rds, itrP->origin, itrP->clr, RQ_SCALE_DEFAULT);
		else if (itrP->type == PTC_SPRITE) rq_Draw(RQ_SPRITE, itrP->rState, itrP->pos, itrP->id, RQ_TEX_NORECT, itrP->origin, itrP->rot, Vector2f(itrP->scale, itrP->scale), itrP->clr_spr);
		else if (itrP->type == PTC_SHARD) {
			va_DrawPolygonReg(VA_LINE, NULL, itrP->v_count, itrP->pos, itrP->rds, itrP->rot, itrP->clr);
		//	sfVertexArray_clear(ptc_va);
		//	for (int i = 0; i <= itrP->v_count; i++) sfVertexArray_append(ptc_va, Vertex(v_Add(itrP->pos, v_RotateD(Vector2f(itrP->rds, 0.f), itrP->rot + i * (360.f / (float)itrP->v_count))), itrP->clr));
		//	rq_Draw(RQ_VA, itrP->rState, ptc_va);
		}
		else if (itrP->type == PTC_BLAST) {
			for (int i = 0; i < 3; i++) {
				float ltRatio = itrP->lifetime / itrP->lifetime_max;
				float rds = itp_Float(itrP->rds_blast, 0.f, clamp(ltRatio * 2.f - itrP->lifetime_max * .25f * i, 0.f, 1.f), itp_Cube);
				sfColor clr = itrP->blast_clr;
				/// FIX THIS DUMBASS
		//		clr.a *= clamp((ltRatio) * 5., 0.f, 1.f);
				clr.a *= .5f;
				va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(itrP->pos, rds * 2.f, rds * 2.f), clr);
			}
		}
		itrP = itrP->next;
	}
}

PtcSystem* ptc_DestroySystem(PtcSystem* _ptcs) {
	PtcSystem* p = _ptcs->prev;
	PtcSystem* n = _ptcs->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_ptcs);
	return n;
}

PtcParticle* ptc_DestroyParticle(PtcParticle* _ptc) {
	PtcParticle* p = _ptc->prev;
	PtcParticle* n = _ptc->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_ptc);
	return n;
}

void ptc_Clear() {
	PtcSystem* itr = ptc_SSentinel->next;
	while (itr != NULL) itr = ptc_DestroySystem(itr);
	log_LogStr(LOG_INFO, "Particle system buffer cleared", sfTrue, sfTrue);

	PtcParticle* itr2 = ptc_PSentinel->next;
	while (itr2 != NULL) itr2 = ptc_DestroyParticle(itr2);
	log_LogStr(LOG_INFO, "Particle buffer cleared", sfTrue, sfTrue);

}

sfColor ptc_RandomColor(sfColor _clr1, sfColor _clr2) { return itp_Color(_clr1, _clr2, rand_unit(3), itp_Linear); }

void ptc_SetPositionPC(PtcSystem* _ptcs, sfVector2f _pos) {
	_ptcs->pos = _pos;
}

void ptc_SetPositionRL(PtcSystem* _ptcs, sfVector2f _pos1, sfVector2f _pos2) {
	_ptcs->pos1 = _pos1;
	_ptcs->pos2 = _pos2;
}

void ptc_SetForce(PtcSystem* _ptcs, float _fmin, float _fmax) {
	_ptcs->force_min = _fmin;
	_ptcs->force_max = _fmax;
}

void ptc_SetDirection(PtcSystem* _ptcs, float _dmin, float _dmax) {
	_ptcs->dir_min = _dmin;
	_ptcs->dir_max = _dmax;
}

void ptc_SetParticlesPerSecond(PtcSystem* _ptcs, int _pps) {
	_ptcs->pps = _pps;
}

void ptc_SetCircleSize(PtcSystem* _ptcs, float _smin, float _smax) {
	if (_ptcs->type != PTC_CIRCLE) {
		log_LogStr(LOG_WARN, "Particle system setup error - SetCircleSize() can only be used on particle systems of type PTC_CIRCLE", sfTrue, sfTrue);
		return;
	}

	_ptcs->size_min = _smin;
	_ptcs->size_max = _smax;
}

void ptc_SetColors(PtcSystem* _ptcs, sfColor _clr1, sfColor _clr2) {
	if (_ptcs->type != PTC_CIRCLE) {
		log_LogStr(LOG_WARN, "Particle system setup error - SetColors() can only be used on particle systems of type PTC_CIRCLE", sfTrue, sfTrue);
		return;
	}

	_ptcs->clr1 = _clr1;
	_ptcs->clr2 = _clr2;
}