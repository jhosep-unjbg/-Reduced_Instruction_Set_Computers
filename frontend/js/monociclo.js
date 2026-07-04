function inicializarMonociclo() {
  calcularMonociclo();

  document
    .getElementById("btnCalcularMonociclo")
    ?.addEventListener("click", calcularMonociclo);
}

function calcularMonociclo() {
  const im = Number(document.getElementById("im").value);
  const rfRead = Number(document.getElementById("rfRead").value);
  const alu = Number(document.getElementById("alu").value);
  const dm = Number(document.getElementById("dm").value);
  const rfWrite = Number(document.getElementById("rfWrite").value);

  if (im <= 0 || rfRead <= 0 || alu <= 0 || dm <= 0 || rfWrite <= 0) {
    alert("Ingrese valores mayores que cero.");
    return;
  }

  const tipoR = im + rfRead + alu + rfWrite;
  const lw = im + rfRead + alu + dm + rfWrite;
  const sw = im + rfRead + alu + dm;
  const beq = im + rfRead + alu;

  const periodo = Math.max(tipoR, lw, sw, beq);
  const frecuenciaMHz = 1000000 / periodo;
  const slack = periodo - beq;
  const eficiencia = (beq / periodo) * 100;

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