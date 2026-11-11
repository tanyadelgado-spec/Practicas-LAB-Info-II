import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

# Directorio del proyecto
base = Path(r"c:\Users\admin\Documents\Tanya\UdeA_20262\Informatic\Info_II_Practicas\Practica_5\Practica_5\datos")

# Leer archivos CSV
posiciones = pd.read_csv(base / "posiciones.csv")
colisiones = pd.read_csv(base / "colisiones.csv")

# Grafica 1. Trayectorias
plt.figure(figsize=(10, 6))

for identificador, grupo in posiciones.groupby("id"):

    grupo = grupo.sort_values("tiempo")

    plt.plot(
        grupo["x"],
        grupo["y"],
        label=f"Particula {identificador}"
    )

plt.xlim(0, 800)
plt.ylim(500, 0)

plt.xlabel("Eje X")
plt.ylabel("Eje Y")
plt.title("Trayectorias de las Partículas")

plt.legend()
plt.grid()

plt.savefig(base / "trayectorias.png")
plt.show()
plt.close()

# Grafica 2. Numero de particulas
cantidad = (
    posiciones.groupby("tiempo")["id"]
    .nunique()
)

plt.figure(figsize=(10, 5))

plt.plot(cantidad.index, cantidad.values)

plt.xlabel("Tiempo (s)")
plt.ylabel("Cantidad de Partículas")
plt.title("Evolución del Número de Partículas")

plt.grid()

plt.savefig(base / "numero_particulas.png")
plt.show()
plt.close()

# Grafica 3. Tipos de colision
if not colisiones.empty:

    eventos = colisiones["tipo"].value_counts()

    plt.figure(figsize=(8, 5))

    eventos.plot(kind="bar")

    plt.xlabel("Tipo de Colisión")
    plt.ylabel("Cantidad de Eventos")
    plt.title("Colisiones Registradas")

    plt.xticks(rotation=0)
    plt.tight_layout()

    plt.savefig(base / "colisiones.png")
    plt.show()
    plt.close()

print("Graficas generadas correctamente.")
