﻿#pragma checksum "..\..\..\AddNewEnemy.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "2699366F94C591C38B13E56C544533DC"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.4952
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms.Integration;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace WPFTools {
    
    
    /// <summary>
    /// AddNewEnemy
    /// </summary>
    public partial class AddNewEnemy : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 6 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Label label1;
        
        #line default
        #line hidden
        
        
        #line 7 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Label label2;
        
        #line default
        #line hidden
        
        
        #line 8 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Label label3;
        
        #line default
        #line hidden
        
        
        #line 9 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Label label4;
        
        #line default
        #line hidden
        
        
        #line 10 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Label label5;
        
        #line default
        #line hidden
        
        
        #line 11 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Label label6;
        
        #line default
        #line hidden
        
        
        #line 12 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.ListBox ActiveEnemyInstances;
        
        #line default
        #line hidden
        
        
        #line 13 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.ListBox CurrentEnemyClassesList;
        
        #line default
        #line hidden
        
        
        #line 14 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Label label7;
        
        #line default
        #line hidden
        
        
        #line 15 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Button CancelButton;
        
        #line default
        #line hidden
        
        
        #line 16 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Button SaveNewEnemyButton;
        
        #line default
        #line hidden
        
        
        #line 17 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.ListBox AvailableEnemyClassesList;
        
        #line default
        #line hidden
        
        
        #line 18 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Button AddInstanceButton;
        
        #line default
        #line hidden
        
        
        #line 19 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.TextBox EnemyNameTextBox;
        
        #line default
        #line hidden
        
        
        #line 20 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.TextBox DisplayNameTextBox;
        
        #line default
        #line hidden
        
        
        #line 21 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.ComboBox EnemyTypeList;
        
        #line default
        #line hidden
        
        
        #line 22 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Button AddClassButton;
        
        #line default
        #line hidden
        
        
        #line 23 "..\..\..\AddNewEnemy.xaml"
        internal System.Windows.Controls.Button RemoveClassButton;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/WPFTools;component/addnewenemy.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\AddNewEnemy.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.label1 = ((System.Windows.Controls.Label)(target));
            return;
            case 2:
            this.label2 = ((System.Windows.Controls.Label)(target));
            return;
            case 3:
            this.label3 = ((System.Windows.Controls.Label)(target));
            return;
            case 4:
            this.label4 = ((System.Windows.Controls.Label)(target));
            return;
            case 5:
            this.label5 = ((System.Windows.Controls.Label)(target));
            return;
            case 6:
            this.label6 = ((System.Windows.Controls.Label)(target));
            return;
            case 7:
            this.ActiveEnemyInstances = ((System.Windows.Controls.ListBox)(target));
            return;
            case 8:
            this.CurrentEnemyClassesList = ((System.Windows.Controls.ListBox)(target));
            return;
            case 9:
            this.label7 = ((System.Windows.Controls.Label)(target));
            return;
            case 10:
            this.CancelButton = ((System.Windows.Controls.Button)(target));
            
            #line 15 "..\..\..\AddNewEnemy.xaml"
            this.CancelButton.Click += new System.Windows.RoutedEventHandler(this.CancelButton_Click);
            
            #line default
            #line hidden
            return;
            case 11:
            this.SaveNewEnemyButton = ((System.Windows.Controls.Button)(target));
            return;
            case 12:
            this.AvailableEnemyClassesList = ((System.Windows.Controls.ListBox)(target));
            return;
            case 13:
            this.AddInstanceButton = ((System.Windows.Controls.Button)(target));
            return;
            case 14:
            this.EnemyNameTextBox = ((System.Windows.Controls.TextBox)(target));
            return;
            case 15:
            this.DisplayNameTextBox = ((System.Windows.Controls.TextBox)(target));
            return;
            case 16:
            this.EnemyTypeList = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 17:
            this.AddClassButton = ((System.Windows.Controls.Button)(target));
            return;
            case 18:
            this.RemoveClassButton = ((System.Windows.Controls.Button)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}
