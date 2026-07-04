const API_URL = "http://localhost:18080";

async function postData(endpoint, data) {
  try {
    const response = await fetch(`${API_URL}${endpoint}`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(data)
    });

    if (!response.ok) {
      throw new Error("Error HTTP: " + response.status);
    }

    return await response.json();

  } catch (error) {
    console.warn("Backend no disponible. Usando simulación local.", error);
    return null;
  }
}

async function getData(endpoint) {
  try {
    const response = await fetch(`${API_URL}${endpoint}`);

    if (!response.ok) {
      throw new Error("Error HTTP: " + response.status);
    }

    return await response.json();

  } catch (error) {
    console.warn("Backend no disponible. Usando datos locales.", error);
    return null;
  }
}