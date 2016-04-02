#ifndef SCENT_H
#define SCENT_H

#include "game_constants.h"
#include "json.h"

#include <memory>
#include <array>

using scent_array = std::array<std::array<int, SEEY *MAPSIZE>, SEEX *MAPSIZE>;

class JsonOut;
class JsonObject;

struct tripoint;

struct scent_layer {
    scent_layer();

    scent_array values;
};

class scent_cache : public JsonSerializer, public JsonDeserializer
{
    public:
        scent_cache();
        ~scent_cache();

        int &get_ref( const tripoint &p );
        const int &get_ref( const tripoint &p ) const;
        // No bounds checks
        int &get_internal( const tripoint &p );

        void update( int minz, int maxz );
        // @todo `bool` mask to avoid decaying indoor scents with rain
        void decay( int zlev, int amount );

        void clear();
        void clear( int zlev );

        scent_layer &get_layer( int zlev );

        void deserialize_level( int zlev, const std::string &line );

        using JsonDeserializer::deserialize;
        virtual void deserialize( JsonIn &jsin ) override;

        using JsonSerializer::serialize;
        virtual void serialize( JsonOut &jsout ) const override;

    private:

        std::array<std::unique_ptr<scent_layer>, OVERMAP_LAYERS> scents;
};

#endif
