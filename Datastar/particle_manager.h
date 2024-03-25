/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Particle and particle system handler.
/// Function prefix: ptc_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "interpolation.h"
#include "texture_manager.h"
#include "window_manager.h"

#define PTC_GRAV_UP_FAST -60.f
#define PTC_GRAV_UP_DEFAULT -20.f
#define PTC_GRAV_UP_SLOW -1.5f
#define PTC_GRAV_NONE 0.f
#define PTC_GRAV_SLOW 1.5f
#define PTC_GRAV_DEFAULT 20.f
#define PTC_GRAV_FAST 60.f

typedef enum {
	PTC_SENTINEL, /// Technical, do not use
	PTC_NONE, /// Not initialized yet
	PTC_CIRCLE, /// Simple circle shape
	PTC_SPRITE, /// Uses a sprite
	PTC_SHARD /// VA-based polygons with randomizable edge count
} PtcType;

typedef enum {
	PTCS_SENTINEL, /// Technical, do not use
	PTCS_NONE, /// Not initialized yet
	PTCS_POINT, /// Spawns particles on a given point
	PTCS_CIRCLE, /// Spawns particles in a radius centered around a given point
	PTCS_RECTANGLE, /// Spawns particles in a rectangle bounded between two points
	PTCS_LINE /// Spawns particles along a line between two points
}PtcSShape;

typedef struct PtcSystem {
	struct PtcSystem* prev;
	struct PtcSystem* next;
	PtcType type;
	PtcSShape shape;
	float lifetime;
	float system_lifetime;
	int pps; /// Particles to be spawned per second
	float force_min; /// Initial speed of particles, lower bound
	float force_max; /// Initial speed of particles, upper bound
	float dir_min;
	float dir_max;
	float gravity;
	sfRenderStates* rState;
	float spawn_timer;

	union {
		struct { /// For circle-type particles
			float size_min;
			float size_max;
			sfColor clr1;
			sfColor clr2;
		};
		struct { /// For sprite-type particles
			char* id;
			float scale_min;
			float scale_max;
			float rot_spd_min;
			float rot_spd_max;
		};
		struct { /// for Shard-type particles
			float rds_min;
			float rds_max;
			int v_min;
			int v_max;
			sfColor vclr1;
			sfColor vclr2;
		};
	};

	union {
		struct { /// For point and circle-type particle systems
			sfVector2f pos;
			float rds;
		};
		struct { /// For rectangle and line-type particle systems
			sfVector2f pos1;
			sfVector2f pos2;
		};
	};
} PtcSystem;
PtcSystem* ptc_SSentinel; /// Sentinel node for the particle system LL

typedef struct PtcParticle {
	struct PtcParticle* prev;
	struct PtcParticle* next;
	PtcType type;
	sfVector2f pos;
	sfVector2f spd;
	sfVector2f origin;
	float lifetime;
	float lifetime_max;
	float gravity;
	sfRenderStates* rState;

	union {
		struct { /// For circle-type particles
			float rds;
			sfColor clr;
		};
		struct { /// For sprite-type particles
			char* id;
			float scale;
			float rot;
			float rot_spd;
			sfColor clr_spr;
		};
		struct { /// For Shard-type particles
			float v_rds;
			sfColor v_clr;
			int v_count;
			float v_rot;
			float v_rot_spd;
		};
	};
} PtcParticle;
PtcParticle* ptc_PSentinel; /// Sentinel node for the particle LL

/// Initializes the particle engine.
void ptc_Init();

/// Creates a new particle system. Also returns it, to make it possible to use the next few setup functions on it.
/// \param _lts - Lifetime of the system. Set to -1.0f to instantly spawn the amount of particles specified by _pps just once
/// \param _ltp - Lifetime of individual particles
/// \param _pps - Particles to be spawned per second. If _lts was set to -1.0f, this many particles will be spawned at once, only once.
/// \param _fmin and _fmax - Minimal and maximal velocity of particles, randomized upon particle creation
/// \param _rmin and _rmax - Minimal and maximal direction of particles (in degrees, from the top, clockwise), randomized upon particle creatio
/// \param _grav - Strength of gravity applied to particles
/// \param _rs - Render states, to apply a shader to all produced particles
PtcSystem* ptc_CreateSystem(float _lts, float _ltp, int _pps, float _fmin, float _fmax, float _rmin, float _rmax, float _grav, sfRenderStates* _rs);

/// Sets the type of a particle system (whether it renders as a circle or a sprite) as well as various settings pertaining to that.
/// \param For a PTC_CIRCLE - Minimum radius (float), maximum radius (float), two colors to build a spectrum (colors)
/// \param For a PTC_SPRITE - Internal texture ID (string), minimum scale (float), maximum scale (float), minimum rotation speed (float), maxinmum rotation speed (float)
/// \param For a PTC_SHARD - Minimum radius (float), maximum radius (float), minimum edge count (int), maximum edge count (int), two colors to build a spectrum (colors)
void ptc_SetType(PtcSystem* _ptcs, PtcType _type, ...);

/// Sets the shape of a particle system (the shape of the particle spawn area) as well as various settings pertaining to that.
/// \param For a PTCS_POINT - Position (2D vector)
/// \param For a PTCS_CIRCLE - Center position (2D vector), radius (float)
/// \param For a PTCS_RECTANGLE - Position of top left corner (2D vector), position of bottom right corner (2D vector)
/// \param For a PTCS_LINE - Positions of the two vertices (2D vectors)
void ptc_SetShape(PtcSystem* _ptcs, PtcSShape _shape, ...);

/// Creates an individual particle. Usable either as part of a system or as a standalone FX.
/// \param _type - Whether the particle should render as a circle or as a sprite
/// \param _pos - Particle coordinates
/// \param _spd - Particle speed
/// \param _lt - Lifetime of the particle
/// \param _grav - Force of gravity applied to the particle
/// \param _rs - Render state, to apply a shader to the particle
/// \param
/// \param The function takes a few extra arguments depending on the selected _type:
/// \param For a PTC_CIRCLE - Radius (float), color (color)
/// \param For a PTC_SPRITE - Internal texture ID (string), scale (float), rotation speed (float)
/// \param For a PTC_SHARD - Radius (float), edge count (int), color (color)
void ptc_CreateParticle(PtcType _type, sfVector2f _pos, sfVector2f _spd, float _lt, float _grav, sfRenderStates* _rs, ...);

/// Ticks the particle engine.
void ptc_Update();

/// Renders all particle effects.
void ptc_Render();

/// Destroys a given particle system.
PtcSystem* ptc_DestroySystem(PtcSystem* _ptcs);

/// Destroys a particle.
PtcParticle* ptc_DestroyParticle(PtcParticle* _ptc);

/// Destroys all particles and particle systems.
void ptc_Clear();

/// Produces a random color from the given spectrum. Set up specifically for particle functions.
sfColor ptc_RandomColor(sfColor _clr1, sfColor _clr2);

void ptc_SetPositionPC(PtcSystem* _ptcs, sfVector2f _pos);
void ptc_SetPositionRL(PtcSystem* _ptcs, sfVector2f _pos1, sfVector2f _pos2);
void ptc_SetForce(PtcSystem* _ptcs, float _fmin, float _fmax);
void ptc_SetDirection(PtcSystem* _ptcs, float _dmin, float _dmax);
void ptc_SetParticlesPerSecond(PtcSystem* _ptcs, int _pps);
void ptc_SetCircleSize(PtcSystem* _ptcs, float _smin, float _smax);
void ptc_SetColors(PtcSystem* _ptcs, sfColor _clr1, sfColor _clr2);