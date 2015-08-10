#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <cmath>

// Taken from http://www.sfml-dev.org/tutorials/2.3/graphics-vertex-array.php

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
    public:
        ParticleSystem(unsigned count);
        void setEmitter(sf::Vector2f position);
        void update(sf::Time elapsed);

    private:
        struct Particle
        {
            sf::Vector2f velocity;
            sf::Time lifetime;
        };

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void resetParticle(unsigned size);

        std::vector<Particle> m_particles;
        sf::VertexArray m_vertices;
        sf::Time m_lifetime;
        sf::Vector2f m_emitter;

};
