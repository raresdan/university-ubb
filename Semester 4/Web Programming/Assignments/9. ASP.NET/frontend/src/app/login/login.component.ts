import {Component, OnInit} from '@angular/core';
import {UserService} from '../user.service';
import { FormBuilder, FormControl, FormGroup, ReactiveFormsModule, Validators } from '@angular/forms';
import { Router, RouterLink } from '@angular/router';
import { CookieService } from 'ngx-cookie-service';

@Component({
    selector: 'app-login',
    standalone: true,
    imports:[
        ReactiveFormsModule,
        RouterLink
      ],
    templateUrl: './login.component.html',
    styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
    loginForm: FormGroup = new FormGroup({});
    constructor(private formBuilder: FormBuilder, private service: UserService, private router: Router, private cookies:CookieService) {}

    ngOnInit() {
        this.loginForm = new FormGroup({
            username: new FormControl('', Validators.required),
            password: new FormControl('', Validators.required)
        });
    }

    onSubmit() {
        this.service.login(this.loginForm.value).subscribe({
            next: response => {
                console.log('User logged in successfully.', response);
                this.cookies.set('loggedIn', "1");
                this.router.navigate(['/users']);
            },
            error: error => {
                console.error('Error logging in:', error);
            }
        });
    }
}