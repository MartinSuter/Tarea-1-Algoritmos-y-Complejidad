import pandas as pd
import matplotlib.pyplot as plt
import os

def generate_matrix_plots():
    csv_path = '../data/measurements/matrix_measurements.csv'
    output_dir = '../data/plots'
    
    os.makedirs(output_dir, exist_ok=True)
    df = pd.read_csv(csv_path)
    
    df_mean = df.groupby(['algorithm', 'n', 'type', 'domain'])['time_ms'].mean().reset_index()

    # Filtramos un caso representativo: matrices densas
    df_plot = df_mean[df_mean['type'] == 'densa']
    
    plt.figure(figsize=(10, 6))
    for algo in df_plot['algorithm'].unique():
        subset = df_plot[df_plot['algorithm'] == algo].sort_values('n')
        plt.plot(subset['n'], subset['time_ms'], marker='o', label=algo)
        
    plt.xscale('log', base=2)
    plt.yscale('log')
    plt.title('Tiempo de Ejecución vs Dimensión (Matrices Densas)')
    plt.xlabel('Dimensión de la matriz (N)')
    plt.ylabel('Tiempo (ms)')
    plt.legend()
    plt.grid(True, which="both", ls="--")
    
    plt.savefig(os.path.join(output_dir, 'matrix_densa.png'))
    print("Gráfico de matrices guardado en data/plots/")

if __name__ == "__main__":
    generate_matrix_plots()