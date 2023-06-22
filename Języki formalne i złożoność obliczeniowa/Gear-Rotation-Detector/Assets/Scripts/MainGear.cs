using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainGear : MonoBehaviour
{
    public float speed;

    void Start()
    {
        
    }

    void Update()
    {
        transform.Rotate(0, 0, speed * Time.deltaTime);
    }

    public void ReverseButton()
    {
        speed *= -1;
    }
}
