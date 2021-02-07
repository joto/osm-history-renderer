-- requires hstore_new, postgis, gist_btree

DROP TABLE IF EXISTS hist_point CASCADE;
CREATE TABLE hist_point (
    id bigint,
    version smallint,
    visible boolean,
    user_id integer,
    user_name text,
    valid_from timestamp without time zone,
    valid_to timestamp without time zone,
    tags hstore,
    layer integer
);
SELECT AddGeometryColumn(
    -- table name
    'hist_point',

    -- column name
    'geom',

    -- SRID (900913 = Spherical Mercator)
    900913,

    -- type
    'POINT',

    -- dimensions
    2
);


DROP TABLE IF EXISTS hist_line CASCADE;
CREATE TABLE hist_line (
    id bigint,
    version smallint,
    minor smallint,
    visible boolean,
    user_id integer,
    user_name text,
    valid_from timestamp without time zone,
    valid_to timestamp without time zone,
    tags hstore,
    layer integer,
    z_order integer
);
SELECT AddGeometryColumn(
    -- table name
    'hist_line',

    -- column name
    'geom',

    -- SRID (900913 = Spherical Mercator)
    900913,

    -- type
    'LINESTRING',

    -- dimensions
    2
);


DROP TABLE IF EXISTS hist_polygon CASCADE;
CREATE TABLE hist_polygon (
    id bigint,
    version smallint,
    minor smallint,
    visible boolean,
    user_id integer,
    user_name text,
    valid_from timestamp without time zone,
    valid_to timestamp without time zone,
    tags hstore,
    layer integer,
    z_order integer,
    area real
);
SELECT AddGeometryColumn(
    -- table name
    'hist_polygon',

    -- column name
    'geom',

    -- SRID (900913 = Spherical Mercator)
    900913,

    -- type -- needs to be changed to generic GEOMETRY later (maybe)
    --'MULTIPOLYGON',
    'POLYGON',

    -- dimensions
    2
);
SELECT AddGeometryColumn(
    -- table name
    'hist_polygon',

    -- column name
    'center',

    -- SRID (900913 = Spherical Mercator)
    900913,

    -- type
    'POINT',

    -- dimensions
    2
);
