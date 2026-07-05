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
      throw new Error("Error en la respuesta del backend");
    }

    return await response.json();
  } catch (error) {
    console.error("Error conectando con backend:", error);
    return null;
  }
}

async function getData(endpoint) {
  try {
    const response = await fetch(`${API_URL}${endpoint}`);

    if (!response.ok) {
      throw new Error("Error en la respuesta del backend");
    }

    return await response.json();
  } catch (error) {
    console.error("Error conectando con backend:", error);
    return null;
  }
}