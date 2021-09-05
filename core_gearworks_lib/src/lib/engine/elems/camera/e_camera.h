#ifndef E_CAMERA_H
#define E_CAMERA_H

#include <gearworks.h>

namespace gearworks {
	class elem_camera {
	private:
		// A struct that holds properties of the camera.
		struct cam_properties_struct {
			// Constructor for a cam_properties_struct object.
			cam_properties_struct();

			/// <summary>
			/// Basic position value of the camera.
			/// </summary>
			vec3 position;

			/// <summary>
			/// Rotation value of the camera.
			/// </summary>
			float roll, pitch, yaw;

			/// <summary>
			/// The coordinate that the camera is currently pointing towards. For example, if it is pointing towards
			/// the center of the world, this would be equal to {0, 0, 0}.
			/// </summary>
			vec3 target_position;
			/// <summary>
			/// The direction that the camera is currently pointing in.
			/// </summary>
			vec3 local_forward_direction;
			/// <summary>
			/// The up direction in local camera space. This is used by Gearworks for its first-person camera system.
			/// </summary>
			vec3 local_up_direction;

			/// <summary>
			/// Direction relative to the camera, e.g. 'left' is to the left of the camera regardless of its rotation.
			/// </summary>
			vec3 forward, left, right, back;

			/// <summary>
			/// Field of view property.
			/// </summary>
			float fov;
		};

		// Applies outstanding transformations
		void apply_transformations(gearworks::renderer *renderer);
	public:
		/// <summary>
		/// Properties of the camera.
		/// </summary>
		cam_properties_struct properties;

		/// <summary>
		/// Updates the camera elem.
		/// </summary>
		void update_camera(renderer *ren);

		/// <summary>
		/// Translates, or moves, the shape by a given distance.
		/// </summary>
		/// <param name="x">Value to move on the X axis.</param>
		/// <param name="y">Value to move on the Y axis.</param>
		/// <param name="z">Value to move on the Z axis.</param>
		inline void translate(float x, float y, float z) { properties.position += vec3(x, y, z); }
		/// <summary>
		/// Translates, or moves, the shape by a given distance.
		/// </summary>
		/// <param name="vect">Value to move on the 3 axes stored as a glm::vec3.</param>
		inline void translate(vec3 vect) { properties.position += vect; }

		/// <summary>
		/// Rotates the shape by a given amount.
		/// </summary>
		/// <param name="x">Value to rotate on the X axis.</param>
		/// <param name="y">Value to rotate on the Y axis.</param>
		/// <param name="z">Value to rotate on the Z axis.</param>
		inline void rotate(float x, float y, float z) { properties.yaw += x; properties.pitch += y; properties.roll += 0; } // subtracted to rotate clockwise by default
		/// <summary>
		/// Rotates the shape by a given amount.
		/// </summary>
		/// <param name="vect">Value to rotate the shape on the 3 axes stored as a glm::vec3.</param>
		inline void rotate(vec3 vect) { properties.yaw += vect.x; properties.pitch += vect.y; properties.roll += 0; } // subtracted to rotate clockwise by default
	};
}

#endif