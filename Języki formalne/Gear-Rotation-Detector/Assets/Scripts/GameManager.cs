using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public GameObject mainGear;
    public GameObject detector;
    public Text detectorInfo;
    void Start()
    {
        Time.timeScale = 0;
        SetDetectorInfo();
        StartCoroutine("DeleyedStart");
    }

    void FixedUpdate()
    {
        SetDetectorInfo();
    }

    IEnumerator DeleyedStart()
    {
        yield return new WaitForSecondsRealtime(0.5f);
        Time.timeScale = 1;
    }

    void SetDetectorInfo()
    {
        detectorInfo.text = "Current Gear Rotation:\n" + detector.GetComponent<DetectorController>().currentRotationDetected;
    }
}
