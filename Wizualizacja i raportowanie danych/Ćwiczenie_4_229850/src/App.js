import { useState, useEffect } from "react";

import { RadioSVGMap } from "react-svg-map";
import USA from "@svg-maps/usa";
import "react-svg-map/lib/index.css";

import "./styles.css";
import "./input-range.css";

const API_KEY = "21a5a33ed3f049f9bbc131308221905";

const colors = [
  "#7fb2f0",
  "#89aee7",
  "#92aadf",
  "#9aa5d7",
  "#a1a1ce",
  "#a79dc6",
  "#ad99be",
  "#b294b5",
  "#b690ad",
  "#ba8ca5",
  "#be879d",
  "#c18395",
  "#c47e8d",
  "#c77a85",
  "#ca757d",
  "#cc7075",
  "#ce6c6e",
  "#d06766",
  "#d1625e",
  "#d35c57",
  "#d4574f",
  "#d55147",
  "#d64b40",
  "#d74538",
  "#d73e30",
  "#d83728",
  "#d82f20",
  "#d92517",
  "#d9180c",
  "#d90000",
];

const locations = [
  {
    name: "Alaska",
    id: "ak",
  },
  {
    name: "Alabama",
    id: "al",
  },
  {
    name: "Arkansas",
    id: "ar",
  },
  {
    name: "Arizona",
    id: "az",
  },
  {
    name: "California",
    id: "ca",
  },
  {
    name: "Colorado",
    id: "co",
  },
  {
    name: "Connecticut",
    id: "ct",
  },
  {
    name: "Washington, DC",
    id: "dc",
  },
  {
    name: "Delaware",
    id: "de",
  },
  {
    name: "Florida",
    id: "fl",
  },
  {
    name: "Georgia",
    id: "ga",
  },
  {
    name: "Hawaii",
    id: "hi",
  },
  {
    name: "Iowa",
    id: "ia",
  },
  {
    name: "Idaho",
    id: "id",
  },
  {
    name: "Illinois",
    id: "il",
  },
  {
    name: "Indiana",
    id: "in",
  },
  {
    name: "Kansas",
    id: "ks",
  },
  {
    name: "Kentucky",
    id: "ky",
  },
  {
    name: "Louisiana",
    id: "la",
  },
  {
    name: "Massachusetts",
    id: "ma",
  },
  {
    name: "Maryland",
    id: "md",
  },
  {
    name: "Maine",
    id: "me",
  },
  {
    name: "Michigan",
    id: "mi",
  },
  {
    name: "Minnesota",
    id: "mn",
  },
  {
    name: "Missouri",
    id: "mo",
  },
  {
    name: "Mississippi",
    id: "ms",
  },
  {
    name: "Montana",
    id: "mt",
  },
  {
    name: "North Carolina",
    id: "nc",
  },
  {
    name: "North Dakota",
    id: "nd",
  },
  {
    name: "Nebraska",
    id: "ne",
  },
  {
    name: "New Hampshire",
    id: "nh",
  },
  {
    name: "New Jersey",
    id: "nj",
  },
  {
    name: "New Mexico",
    id: "nm",
  },
  {
    name: "Nevada",
    id: "nv",
  },
  {
    name: "New York",
    id: "ny",
  },
  {
    name: "Ohio",
    id: "oh",
  },
  {
    name: "Oklahoma",
    id: "ok",
  },
  {
    name: "Oregon",
    id: "or",
  },
  {
    name: "Pennsylvania",
    id: "pa",
  },
  {
    name: "Rhode Island",
    id: "ri",
  },
  {
    name: "South Carolina",
    id: "sc",
  },
  {
    name: "South Dakota",
    id: "sd",
  },
  {
    name: "Tennessee",
    id: "tn",
  },
  {
    name: "Texas",
    id: "tx",
  },
  {
    name: "Utah",
    id: "ut",
  },
  {
    name: "Virginia",
    id: "va",
  },
  {
    name: "Vermont",
    id: "vt",
  },
  {
    name: "Washington",
    id: "wa",
  },
  {
    name: "Wisconsin",
    id: "wi",
  },
  {
    name: "West Virginia",
    id: "wv",
  },
  {
    name: "Wyoming",
    id: "wy",
  },
];

const App = () => {
  const [selectedLocation, setSelectedLocation] = useState("Alaska");
  const [selectedHour, setSelectedHour] = useState(12);
  const [temperature, setTemperature] = useState("");
  const [pressure, setPressure] = useState("");

  const date = new Date();

  let elements;
  if (!elements) {
    elements = document.querySelector(":root");
  }

  const getAllWeatherAndColor = async () => {
    for (let state of locations) {
      console.log(state);

      const apiCall = await fetch(
        `https://api.weatherapi.com/v1/forecast.json?key=${API_KEY}&q=${state.name}&days=1&aqi=no&alerts=no`
      );

      const response = await apiCall.json();

      const temperature =
        response.forecast.forecastday[0].hour[selectedHour].temp_c;

      colorState(temperature, state);
    }
  };

  function colorState(temperature, state) {
    let color;
    if (temperature <= 10) color = colors[0];
    else if (temperature >= 29) color = colors[29];
    else color = colors[Number(temperature).toFixed(0)];

    let element = document.getElementById(state.id);
    element.style.fill = color;
  }

  function color_coding() {
    let color;
    if (temperature <= 10) color = colors[0];
    else if (temperature >= 29) color = colors[29];
    else color = colors[Number(temperature).toFixed(0)];
    console.log(Number(temperature).toFixed(0));
    elements.style.setProperty("--fill", color);
  }

  const getWeather = async () => {
    const apiCall = await fetch(
      `https://api.weatherapi.com/v1/forecast.json?key=${API_KEY}&q=${selectedLocation}&days=1&aqi=no&alerts=no`
    );

    const response = await apiCall.json();

    const temperature =
      response.forecast.forecastday[0].hour[selectedHour].temp_c;

    const pressure =
      response.forecast.forecastday[0].hour[selectedHour].pressure_mb;

    setTemperature(temperature);
    setPressure(pressure);
  };

  useEffect(() => {
    getWeather();
  }, [selectedHour, selectedLocation]);

  useEffect(() => {
    color_coding();
    getAllWeatherAndColor();
  }, [temperature]);

  return (
    <div className="app-container">
      <div className="map-container">
        <RadioSVGMap
          map={USA}
          className="map"
          onChange={(event) => {
            const stateName = Object.entries(event)[1][1].name;
            setSelectedLocation(stateName);
          }}
        />
      </div>
      <div className="right-container">
        <div className="inner-right-container">
          <h1>Selected State: {selectedLocation}</h1>
          <div className="range-input-container">
            <label htmlFor="input">
              {date.toLocaleDateString()} |{" "}
              <strong>{selectedHour + ":00"}</strong>
            </label>
            <input
              id="input"
              type="range"
              className="range-input"
              value={selectedHour}
              min="0"
              max="23"
              step="1"
              onChange={(e) => {
                setSelectedHour(e.target.value);
              }}
            />
          </div>
          <div className="data-container">
            <p>
              Temperature [°C]: <strong>{temperature}</strong>
            </p>
            <p>
              Pressure [hPa]: <strong>{pressure}</strong>
            </p>
          </div>
        </div>
      </div>
    </div>
  );
};

export default App;




