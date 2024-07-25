import React, { useEffect, useState } from 'react';
import { MapContainer, TileLayer, Marker, Popup } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';
import L from 'leaflet';
import { createClient } from '@supabase/supabase-js';

const supabaseUrl = 'SUPABASE_URL';
const supabaseKey = 'SUPABASE_API_KEY';

const supabase = createClient(supabaseUrl, supabaseKey);

// Define the bus icon
const busIcon = new L.Icon({
  iconUrl: '/images/bus.png', // Path to your bus image
  iconSize: [40, 40], // Size of the icon
  iconAnchor: [20, 40], // Point of the icon which will correspond to marker's location
  popupAnchor: [0, -40] // Point from which the popup should open relative to the iconAnchor
});

const Map = () => {
  const [locations, setLocations] = useState([]);

  useEffect(() => {
    const fetchLocations = async () => {
      const { data, error } = await supabase
        .from('GPS')
        .select('*') 
        .order('updated_at', { ascending: false });
      if (error) console.error('Error fetching data:', error);
      else setLocations(data);
    };

    fetchLocations();
    const interval = setInterval(fetchLocations, 1000); // Fetch every 1 second

    return () => clearInterval(interval); // Cleanup interval on component unmount
  }, []);

  return (
    <MapContainer center={[28.529111, 77.575276]} zoom={15} style={{ height: "100vh", width: "100%" }}>  // Default View Location
      <TileLayer
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
      />
      {locations.map(loc => (
        <Marker key={loc.id} position={[loc.LAT, loc.LONG]} icon={busIcon}>
          <Popup>
            Shuttle ID: {loc.id} <br /> Timestamp: {new Date(loc.updated_at).toLocaleString()}    // Choose what to display on pop-up
          </Popup>
        </Marker>
      ))}
    </MapContainer>
  );
};

export default Map;
