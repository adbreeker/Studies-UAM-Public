using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DetectorController : MonoBehaviour
{
    public Transform raycaster1, raycaster2;
    public Vector2 direction = Vector2.right;
    public float maxDistance;
    public string currentRotationDetected = "<color=white>Null</color>";

    float lastD1 = 0, lastD2 = 0;

    void Start()
    {
        currentRotationDetected ="<color=white>Null</color>";
    }

    void FixedUpdate()
    {
        float dist1 = 0, dist2 = 0;

        RaycastHit2D det1 = Physics2D.Raycast(raycaster1.position, direction, maxDistance);
        if(det1.collider != null)
        {
            dist1 = det1.distance;
        }
        RaycastHit2D det2 = Physics2D.Raycast(raycaster2.position, direction, maxDistance);
        if (det2.collider != null)
        {
            dist2 = det2.distance;
        }


        if(Mathf.Abs(lastD1 - lastD2) < 0.001f)
        {
            if(Mathf.Abs(dist1 - dist2) > 0.1f)
            {
                if(dist1 < dist2)
                {
                    currentRotationDetected = "<color=green>Clockwise</color>";
                }
                if(dist1 > dist2)
                {
                    currentRotationDetected = "<color=red>CounterClockwise</color>";
                }
            }
        }

        lastD1 = dist1;
        lastD2 = dist2;
    }
}
