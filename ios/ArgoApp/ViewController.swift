//
//  ViewController.swift
//  ArgoApp
//
//  Created by Manu Wallner on 29.06.2016.
//
//

import UIKit

class ViewController: UIViewController {
    let getter = XFMyRecordGetter.create()
    let delegate = RecordGetterDelegate()
    
    class RecordGetterDelegate : NSObject, XFMyRecordGetterDelegate {
        func receiveRecord(record: XFMyRecord) {
            print("Receiving a record from C++...")
            print("ID: \(record.id)")
            for text in record.texts {
                print(text)
            }
            print("Our optional is also: \(record.optionalTest)")
        }
        
        func shouldGetRecord() -> Bool {
            print("C++ wants to know if we should receive a record")
            return true
        }
    }
    
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

