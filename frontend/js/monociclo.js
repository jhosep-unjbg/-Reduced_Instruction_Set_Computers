async function inicializarMonociclo() {
  console.log("Inicializando Monociclo...");

  const btn = document.getElementById("btnCalcularMonociclo");
  console.log("Botón Monociclo:", btn);

  if (!btn) {
    console.error("No se encontró el botón btnCalcularMonociclo");
    return;
  }

  btn.addEventListener("click", calcularMonociclo);
}

async function calcularMonociclo() {
  console.log("Click en Calcular Monociclo");

  const im = Number(document.getElementById("im").value);
  const rfRead = Number(document.getElementById("rfRead").value);
  const alu = Number(document.getElementById("alu").value);
  const dm = Number(document.getElementById("dm").value);
  const rfWrite = Number(document.getElementById("rfWrite").value);

  if (im <= 0 || rfRead <= 0 || alu <= 0 || dm <= 0 || rfWrite <= 0) {
    alert("Ingrese valores mayores que cero.");
    return;
  }

  const resultado = await postData("/api/monociclo", {
    im,
    rfRead,
    alu,
    dm,
    rfWrite
  });

  if (!resultado) {
    alert("No se pudo conectar con el backend Crow.");
    return;
  }

  const tipoR = resultado.tipoR;
  const lw = resultado.lw;
  const sw = resultado.sw;
  const beq = resultado.beq;
  const periodo = resultado.periodo;
  const frecuenciaMHz = resultado.frecuenciaMHz;
  const slack = resultado.slack;
  const eficiencia = resultado.eficiencia;

  document.getElementById("tipoR").textContent = tipoR + " ps";
  document.getElementById("lw").textContent = lw + " ps";
  document.getElementById("sw").textContent = sw + " ps";
  document.getElementById("beq").textContent = beq + " ps";

  document.getElementById("cardTipoR").textContent = tipoR + " ps";
  document.getElementById("cardLw").textContent = lw + " ps";
  document.getElementById("cardSw").textContent = sw + " ps";
  document.getElementById("cardBeq").textContent = beq + " ps";

  document.getElementById("statPeriodo").textContent = periodo + " ps";
  document.getElementById("statFrecuencia").textContent = frecuenciaMHz.toFixed(2) + " MHz";
  document.getElementById("statSlack").textContent = slack + " ps";
  document.getElementById("statEficienciaMono").textContent = eficiencia.toFixed(1) + "%";
}