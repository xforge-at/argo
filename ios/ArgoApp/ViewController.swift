//
//  ViewController.swift
//  ArgoApp
//
//  Created by Manu Wallner on 29.06.2016.
//
//

import UIKit
import Argo

class ViewController: UIViewController {
    let getter = XFMyRecordGetter.create()
    let delegate = RecordGetterDelegate()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        getter.setDelegate(delegate)
        getter.getAsyncRecord("Hello from Swift")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

