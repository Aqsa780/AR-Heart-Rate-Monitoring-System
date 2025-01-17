using System.IO.Ports;
using UnityEngine;

public class HeartRateMonitor : MonoBehaviour {
    public string portName = "COM3";
    private SerialPort serialPort;
    public Animator heartAnimator;

    void Start() {
        serialPort = new SerialPort(portName, 9600);
        serialPort.Open();
    }

    void Update() {
        if (serialPort.IsOpen) {
            try {
                string data = serialPort.ReadLine();
                int bpm = int.Parse(data);
                UpdateHeartAnimation(bpm);
            } catch { }
        }
    }

    void UpdateHeartAnimation(int bpm) {
        float speed = bpm / 60.0f; // Adjust as needed
        heartAnimator.speed = speed;
        // Additional logic for color changes
    }

    void OnApplicationQuit() {
        if (serialPort != null && serialPort.IsOpen) serialPort.Close();
    }
}

