<h1 align="center">TrackWheels</h1><p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=arduino,cpp,javascript,nodejs,react,bash,git,vercel,supabase" />
  </a>
</p>
<img src="images/map1.png" alt="TrackWheels">

<h2>Overview</h2>
<p>TrackWheels is an ESP-based vehicle tracking system designed to monitor and display the real-time location of vehicles. This project consists of two main components: the hardware setup and the software for map visualization.</p>

<h2>Hardware Setup</h2>
<p>The hardware component of TrackWheels includes:</p>
<ul>
    <li><strong>ESP8266 Development Board</strong>: A low-cost Wi-Fi microchip with full TCP/IP stack and microcontroller capability.</li>
    <li><strong>Neo6M GPS Module</strong>: A GPS module used to retrieve the geographical coordinates of the vehicle.</li>
</ul>
<p>The ESP8266 board reads the GPS data from the Neo6M module and sends the vehicle coordinates to a Supabase cloud database.</p>

<h2>Software</h2>
<p>The software component is built using ReactJS and is responsible for displaying a map that tracks the real-time location of the vehicle. It collects the coordinates stored in the Supabase database and visualizes them on the map.</p>

<h2>Installation and Setup</h2>

<h3>Hardware</h3>
<div align="center">
  <img src="images/circuit.jpeg" alt="Circuit" width="500" height="500">
</div>

<ol>
    <li><strong>Connect the ESP8266 to the Neo6M GPS Module</strong>:
        <ul>
            <li>VCC of Neo6M to 3.3V of ESP8266</li>
            <li>GND of Neo6M to GND of ESP8266</li>
            <li>TX of Neo6M to D1 of ESP8266</li>
        </ul>
    </li>
    <li><strong>Upload the firmware</strong>:
        <p>Use the Arduino IDE to write and upload the code to the ESP8266. The code should read the GPS data and send it to the Supabase database.</p>
    </li>
    <li><strong>Supabase Setup</strong>:
        <ul>
            <li>Create a new project in Supabase.</li>
            <li>Set up a table to store the vehicle coordinates (latitude, longitude, timestamp).</li>        
          <pre><code>
            CREATE TABLE GPS (
            id SERIAL PRIMARY KEY,
            LAT FLOAT NOT NULL,
            LONG FLOAT NOT NULL,
            updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL
            );
          </code></pre>
            <li>Note down the <code>supabaseUrl</code> and <code>supabaseAPIKey</code>.</li>
        </ul>
    </li>
</ol>

<h3>Software</h3>
<ol>
    <li><strong>Clone the repository</strong>:
        <pre><code>git clone https://github.com/VarunMusham/TrackWheels.git
cd TrackWheels
        </code></pre>
    </li>
    <li><strong>Install the dependencies</strong>:
        <pre><code>npm install
        </code></pre>
    </li>
    <li><strong>Add Supabase Credentials</strong>:
        <p>Add your credentials in TrackWheels.ino and Map.js files</p>
    </li>
    <li><strong>Run the application</strong>:
        <pre><code>npm start
        </code></pre>
    </li>
    <li><strong>Open the application</strong>:
        <p>Navigate to <a href="http://localhost:3000">http://localhost:3000</a> in your web browser to see the map displaying the real-time location of the vehicle.</p>
    </li>
</ol>

<h2>Usage</h2>
<ul>
    <li>Turn on the hardware setup.</li>
    <li>Ensure the ESP8266 is connected to a Wi-Fi network.</li>
    <li>Start the React application to view the real-time tracking on the map.</li>
    <li>You can extract other values from Neo 6M module. (refer datasheet).</li>
</ul>

<h2>Contributing</h2>
<p>Contributions are welcome! Please fork the repository and create a pull request with your changes.</p>

<h2>Deployment</h2>
<p>You can deploy the Map website using services like Vercel, Netlify and many more. Make sure to select correct framework while deploying</p>
